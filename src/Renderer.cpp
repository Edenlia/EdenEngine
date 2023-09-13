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
                (int) camera->getWidth() * (int) camera->getHeight(),1.0f);
        this->frameBuffer = std::vector<glm::vec3>(
                (int) camera->getWidth() * (int) camera->getHeight(), glm::vec3(0, 0, 0));
    }

    void Renderer::draw() {
        float nearPlane = camera->getNearPlane();
        float farPlane = camera->getFarPlane();
        for (auto &actor : scene->getActors()) {
            for (auto &triangle : actor->getModel()->getTriangles()) {
                auto* screenTriangle = new Triangle();
                glm::vec3 worldPos[3];
                for (int i = 0; i < 3; i++) {
                    // model, view transform
                    glm::vec4 vertex = actor->getModelMatrix() * triangle->getVertex(i);
                    vertex = viewMatrix * vertex;

                    worldPos[i] = glm::vec3(vertex);

                    vertex /= vertex.w;
                    float bufferZ = vertex.z; // Depth of z, we store the view depth because that is linear
                    // projection transform
                    vertex = projectionMatrix * vertex;
                    vertex /= vertex.w;
                    vertex.x = (vertex.x + 1.0f) * (float) camera->getWidth() / 2.0f; // NDC to screen, [-1,1] to [0, width]
                    vertex.y = (vertex.y + 1.0f) * (float) camera->getHeight() / 2.0f; // NDC to screen, [-1,1] to [0, height]
                    vertex.z = bufferZ; // z store the depth of the vertex in view coordinate, it is linear, near plane to far plane
                    vertex.w = (bufferZ - nearPlane) / (farPlane - nearPlane); // w store the depth of the vertex, [0, 1], it is also linear
                    screenTriangle->setVertex(i, glm::vec4(vertex.x, vertex.y, vertex.z, vertex.w));
                    screenTriangle->setColor(i, triangle->getColor(i));
                    screenTriangle->setNormal(i, triangle->getNormal(i));
                    screenTriangle->setUV(i, triangle->getUV(i));
                    screenTriangle->texture = triangle->texture;
                }
                drawTriangle(screenTriangle, worldPos);
            }
        }
    }

    // draw triangle, the param triangle's z value is view coordinate's z value
    void Renderer::drawTriangle(Triangle* triangle, glm::vec3 worldPos[3]) {
        glm::vec4 v0 = triangle->getVertex(0);
        glm::vec4 v1 = triangle->getVertex(1);
        glm::vec4 v2 = triangle->getVertex(2);

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
                    // z has more precision than depth, so we use z to interpolate
                    float z = 1 / (alpha / v0.z + beta / v1.z + gamma / v2.z);
                    // w store in depth buffer
                    float w = 1 / (alpha / v0.w + beta / v1.w + gamma / v2.w);
                    if (w < depthBuffer[getIndex(x,y)] && w <= 1 && w >= 0) {
                        depthBuffer[getIndex(x,y)] = w;
                        glm::vec3 fragmentColor =  z * (alpha * triangle->getColor(0) / triangle->getVertex(0).z +
                                                         beta * triangle->getColor(1) / triangle->getVertex(1).z +
                                                         gamma * triangle->getColor(2) / triangle->getVertex(2).z);
                        glm::vec3 fragmentNormal = z * (alpha * triangle->getNormal(0) / triangle->getVertex(0).z +
                                                         beta * triangle->getNormal(1) / triangle->getVertex(1).z +
                                                         gamma * triangle->getNormal(2) / triangle->getVertex(2).z);
                        glm::vec2 fragmentUV = z * (alpha * triangle->getUV(0) / triangle->getVertex(0).z +
                                                         beta * triangle->getUV(1) / triangle->getVertex(1).z +
                                                         gamma * triangle->getUV(2) / triangle->getVertex(2).z);
                        glm::vec3 fragmentPosition = z * (alpha * worldPos[0] / triangle->getVertex(0).z +
                                                            beta * worldPos[1] / triangle->getVertex(1).z +
                                                            gamma * worldPos[2] / triangle->getVertex(2).z);

                        fragmentPayload payload = {fragmentColor, fragmentNormal, fragmentUV, w, fragmentPosition, triangle->texture};

                        frameBuffer[getIndex(x,y)] = fragmentShader(payload);
                    }
                }
            }
        }
    }

    // use 2D cross product to determine if p is inside triangle abc
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

    glm::vec3 Renderer::fragmentShader(const fragmentPayload &payload) {
        glm::vec3 color = glm::vec3(0, 0, 0);
        switch (renderMode) {
            case RenderMode::RASTERIZATION:
            {
                if (payload.material != nullptr) {
                    color = payload.material->getColor(payload.uv.x, payload.uv.y);
                } else {
                    color = payload.color / 255.0f;
                }
                break;
            }

            case NORMAL:
            {
                color = (payload.normal + glm::vec3(1, 1, 1)) / 2.f;
                break;
            }

            case BLINN_PHONG:
            {
                glm::vec3 albedo = payload.material ? payload.material->getColor(payload.uv.x, payload.uv.y) : payload.color / 255.0f;
                glm::vec3 ka = glm::vec3(0.001, 0.001, 0.001);
                glm::vec3 kd = albedo;
                glm::vec3 ks = glm::vec3(0.7937, 0.7937, 0.7937);
                float p = 100.f;


                for (auto* light : scene->getLights()) {
                    glm::vec3 I = light->getColor() * light->getIntensity() / 255.0f;
                    float r2 = glm::dot(light->getPosition() - payload.worldPos, light->getPosition() - payload.worldPos);
                    glm::vec3 wi = glm::normalize(light->getPosition() - payload.worldPos);
                    glm::vec3 n = glm::normalize(payload.normal);
                    glm::vec3 wo = glm::normalize(camera->getPosition() - payload.worldPos);
                    glm::vec3 h = glm::normalize(wi + wo);
                    glm::vec3 Ld = glm::vec3(0, 0, 0), Ls = glm::vec3(0, 0, 0), La = glm::vec3(0, 0, 0);
                    Ld = kd * I * std::max(glm::dot(n, wi), 0.f) / r2;
                    Ls = ks * I * std::pow(std::max(glm::dot(n, h), 0.0f), p) / r2;
                    La = ka * I;
                    color += Ld + Ls + La;
                }
                break;
            }

            case DEPTH:
            {
                color = glm::vec3(payload.depth, payload.depth, payload.depth);
                break;
            }
        }
//        std::cout << "color: " << color.x << " " << color.y << " " << color.z << std::endl;
        return color;
    }
} // EE