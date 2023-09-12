//
// Created by zsy01 on 2023/9/8.
//

#include "Renderer.hpp"
#include "util/EEMath.hpp"
#include <limits>
#include <array>

namespace EE {
    Renderer::Renderer(Scene *scene, Camera *camera) {
        this->scene = scene;
        this->camera = camera;
        this->viewMatrix = this->camera->getViewMatrix();
        this->projectionMatrix = this->camera->getProjectionMatrix();
        this->depthBuffer = std::vector<float>(
                (int) camera->getWidth() * (int) camera->getHeight(),std::numeric_limits<float>::max());
        this->frameBuffer = std::vector<glm::vec3>(
                (int) camera->getWidth() * (int) camera->getHeight(), glm::vec3(0, 0, 0));
    }

    void Renderer::draw() {
        for (auto &actor : scene->getActors()) {
            for (auto &triangle : actor->getModel()->getTriangles()) {
                auto* screenTriangle = new Triangle();
                for (int i = 0; i < 3; i++) {
                    // model, view transform
                    glm::vec4 vertex = actor->getModelMatrix() * triangle->getVertex(i);
                    vertex = viewMatrix * vertex;
                    vertex /= vertex.w;
                    float bufferZ = vertex.z; // Depth of z, we store the view depth because that is linear
                    // projection transform
                    vertex = projectionMatrix * vertex;
                    vertex /= vertex.w;
                    vertex.x = (vertex.x + 1.0f) * (float) camera->getWidth() / 2.0f; // NDC to screen, [-1,1] to [0, width]
                    vertex.y = (vertex.y + 1.0f) * (float) camera->getHeight() / 2.0f; // NDC to screen, [-1,1] to [0, height]
                    vertex.z = bufferZ; // z store the depth of the vertex in view coordinate, it is linear, near plane to far plane
                    screenTriangle->setVertex(i, glm::vec3(vertex.x, vertex.y, vertex.z));
                    screenTriangle->setColor(i, triangle->getColor(i));
                    screenTriangle->setNormal(i, triangle->getNormal(i));
                }
                drawTriangle(screenTriangle);
            }
        }
    }

    // draw triangle, the param triangle's z value is view coordinate's z value
    void Renderer::drawTriangle(Triangle* triangle) {
        glm::vec3 v0 = triangle->getVertex(0);
        glm::vec3 v1 = triangle->getVertex(1);
        glm::vec3 v2 = triangle->getVertex(2);

        glm::vec3 c0 = triangle->getColor(0);
        glm::vec3 c1 = triangle->getColor(1);
        glm::vec3 c2 = triangle->getColor(2);

        // Bounding box
        int minX = std::min(v0.x, std::min(v1.x, v2.x));
        int maxX = std::max(v0.x, std::max(v1.x, v2.x));
        int minY = std::min(v0.y, std::min(v1.y, v2.y));
        int maxY = std::max(v0.y, std::max(v1.y, v2.y));

        // Clipping
        minX = std::max(0, minX);
        maxX = std::min((int) camera->getWidth() - 1, maxX);
        minY = std::max(0, minY);
        maxY = std::min((int) camera->getHeight() - 1, maxY);

        // Rasterization
        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                glm::vec3 p((float) x + 0.5f, (float) y + 0.5f, 0.0f);
                if (insideTriangle(p, v0, v1, v2)) {
                    auto[alpha, beta, gamma] = computeBarycentric2D(p.x, p.y, v0, v1, v2);
                    // interpolate z buffer: https://zhuanlan.zhihu.com/p/144331875
                    float z = 1 / (alpha / v0.z + beta / v1.z + gamma / v2.z);
                    if (z < depthBuffer[getIndex(x,y)] && z <= this->camera->getFarPlane() && z >= this->camera->getNearPlane()) {
                        depthBuffer[getIndex(x,y)] = z;
//                        frameBuffer[getIndex(x,y)] = z * (alpha * c0 / v0.z + beta * c1 / v1.z + gamma * c2 / v2.z);
                        frameBuffer[getIndex(x,y)] = renderPixel(x, y, z, alpha, beta, gamma, triangle);
                    }
                }
            }
        }
    }

    bool Renderer::insideTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
        glm::vec2 ab = glm::vec2(b.x - a.x, b.y - a.y);
        glm::vec2 bc = glm::vec2(c.x - b.x, c.y - b.y);
        glm::vec2 ca = glm::vec2(a.x - c.x, a.y - c.y);
        glm::vec2 ap = glm::vec2(p.x - a.x, p.y - a.y);
        glm::vec2 bp = glm::vec2(p.x - b.x, p.y - b.y);
        glm::vec2 cp = glm::vec2(p.x - c.x, p.y - c.y);

        float c1 = ab.x * ap.y - ab.y * ap.x;
        float c2 = bc.x * bp.y - bc.y * bp.x;
        float c3 = ca.x * cp.y - ca.y * cp.x;


        return (c1 >= 0 && c2 >= 0 && c3 >= 0) || (c1 <= 0 && c2 <= 0 && c3 <= 0);
    }

    glm::vec3 Renderer::renderPixel(int x, int y, float z_value, float alpha, float beta, float gamma, const Triangle *triangle) {
        glm::vec3 color;
        switch (renderMode) {
            case RenderMode::RASTERIZATION:
                color = z_value * (alpha * triangle->getColor(0) / triangle->getVertex(0).z +
                                  beta * triangle->getColor(1) / triangle->getVertex(1).z +
                                  gamma * triangle->getColor(2) / triangle->getVertex(2).z);
                break;
            case NORMAL:
//                std::cout << "v0's normal: " << triangle->getNormal(0).x << " " << triangle->getNormal(0).y << " " << triangle->getNormal(0).z << std::endl;
//                std::cout << "v1's normal: " << triangle->getNormal(1).x << " " << triangle->getNormal(1).y << " " << triangle->getNormal(1).z << std::endl;
//                std::cout << "v2's normal: " << triangle->getNormal(2).x << " " << triangle->getNormal(2).y << " " << triangle->getNormal(2).z << std::endl;
                glm::vec3 normal = z_value * (alpha * triangle->getNormal(0) / triangle->getVertex(0).z +
                                              beta * triangle->getNormal(1) / triangle->getVertex(1).z +
                                              gamma * triangle->getNormal(2) / triangle->getVertex(2).z);
//                std::cout << "normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
                color = (normal + glm::vec3(1, 1, 1)) / 2.f;
                break;
//            case WIREFRAME:
//                break;
//            case VERTEX:
//                break;
//            case DEPTH:
//                break;
//            case TEXTURE:
//                break;
        }
//        std::cout << "color: " << color.x << " " << color.y << " " << color.z << std::endl;
        return color;
    }
} // EE