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
                (int) scene->getWidth() * (int) scene->getHeight(),std::numeric_limits<float>::max());
        this->frameBuffer = std::vector<glm::vec3>(
                (int) scene->getWidth() * (int) scene->getHeight(), glm::vec3(0, 0, 0));
    }

    void Renderer::draw() {
        for (auto &object : scene->getObjects()) {
            for (auto &triangle : object->getTriangles()) {
                auto* screenTriangle = new Triangle();
                for (int i = 0; i < 3; i++) {
                    glm::vec4 vertex = viewMatrix * glm::vec4(triangle->getVertex(i), 1.0f);
//                    std::cout << "view vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
                    vertex /= vertex.w;
                    float bufferZ = vertex.z; // Depth of z, we store the view depth because that is linear

                    vertex = projectionMatrix * vertex;
                    vertex /= vertex.w;
//                    std::cout << "projection vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
                    vertex.x = (vertex.x + 1.0f) * (float) scene->getWidth() / 2.0f; // NDC to screen, [-1,1] to [0, width]
                    vertex.y = (vertex.y + 1.0f) * (float) scene->getHeight() / 2.0f; // NDC to screen, [-1,1] to [0, height]
                    vertex.z = bufferZ; // z store the depth of the vertex in view coordinate, it is linear, near plane to far plane
                    screenTriangle->setVertex(i, glm::vec3(vertex.x, vertex.y, vertex.z));
                    screenTriangle->setColor(i, triangle->getColor(i));
                }

//                std::cout << "screenTriangle v0: " << "v0: " << screenTriangle->getVertex(0).x << " " << screenTriangle->getVertex(0).y << " " << screenTriangle->getVertex(0).z << std::endl;
//                std::cout << "screenTriangle v1: " << "v1: " << screenTriangle->getVertex(1).x << " " << screenTriangle->getVertex(1).y << " " << screenTriangle->getVertex(1).z << std::endl;
//                std::cout << "screenTriangle v2: " << "v2: " << screenTriangle->getVertex(2).x << " " << screenTriangle->getVertex(2).y << " " << screenTriangle->getVertex(2).z << std::endl;

                drawTriangle(screenTriangle);
            }
        }
    }

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
        maxX = std::min((int) scene->getWidth() - 1, maxX);
        minY = std::max(0, minY);
        maxY = std::min((int) scene->getHeight() - 1, maxY);

        // Rasterization
        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                glm::vec3 p((float) x + 0.5f, (float) y + 0.5f, 0.0f);
                if (insideTriangle(p, v0, v1, v2)) {
                    auto[alpha, beta, gamma] = computeBarycentric2D(p.x, p.y, v0, v1, v2);
//                    std::cout << "alpha: " << alpha << " beta: " << beta << " gamma: " << gamma << std::endl;
                    // interpolate z buffer: https://zhuanlan.zhihu.com/p/144331875
                    float z = 1 / (alpha / v0.z + beta / v1.z + gamma / v2.z);
                    if (z < depthBuffer[getIndex(x,y)] && z <= this->camera->getFarPlane() && z >= this->camera->getNearPlane()) {
                        depthBuffer[getIndex(x,y)] = z;
                        frameBuffer[getIndex(x,y)] = z * (alpha * c0 / v0.z + beta * c1 / v1.z + gamma * c2 / v2.z);
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


} // EE