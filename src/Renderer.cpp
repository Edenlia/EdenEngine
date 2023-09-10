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
                    std::cout << "projection vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
                    vertex.x = (vertex.x + 1.0f) * (float) scene->getWidth() / 2.0f; // NDC to screen, [-1,1] to [0, width]
                    vertex.y = (vertex.y + 1.0f) * (float) scene->getHeight() / 2.0f; // NDC to screen, [-1,1] to [0, height]
                    vertex.z = bufferZ; // z store the depth of the vertex in view coordinate, it is linear, near plane to far plane
                    screenTriangle->setVertex(i, glm::vec3(vertex.x, vertex.y, vertex.z));
                    screenTriangle->setColor(i, triangle->getColor(i));
                }

//                std::cout << "screenTriangle: " << "v0: " << screenTriangle->getVertex(0).x << " " << screenTriangle->getVertex(0).y << " " << screenTriangle->getVertex(0).z << std::endl;

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
//                std::cout << "start draw" << std::endl;
                if (insideTriangle(p, v0, v1, v2)) {
//                    std::cout << "insideTriangle!" << std::endl;
                    auto[alpha, beta, gamma] = computeBarycentric2D(p.x, p.x, v0, v1, v2);
                    // interpolate z buffer: https://zhuanlan.zhihu.com/p/144331875
                    float z = 1 / (alpha / v0.z + beta / v1.z + gamma / v2.z);
                    if (z < depthBuffer[y + x * scene->getWidth()] && z <= this->camera->getFarPlane() && z >= this->camera->getNearPlane()) {
//                        std::cout << "update!" << std::endl;
                        depthBuffer[y + x * scene->getWidth()] = z;
                        frameBuffer[y + x * scene->getWidth()] = z * (alpha * c0 / v0.z + beta * c1 / v1.z + gamma * c2 / v2.z);
                    }
                }
            }
        }
    }

    bool Renderer::insideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
        glm::vec3 ab = b - a;
        glm::vec3 bc = c - b;
        glm::vec3 ca = a - c;
        glm::vec3 ap = p - a;
        glm::vec3 bp = p - b;
        glm::vec3 cp = p - c;

        glm::vec3 abp = glm::cross(ab, ap);
        glm::vec3 bcp = glm::cross(bc, bp);
        glm::vec3 cap = glm::cross(ca, cp);

        return (glm::dot(abp, bcp) >= 0) && (glm::dot(bcp, cap) >= 0);
    }


} // EE