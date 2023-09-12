//
// Created by zsy01 on 2023/9/8.
//

#ifndef EDENENGINE_RENDERER_HPP
#define EDENENGINE_RENDERER_HPP

#include "Scene.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include <iostream>


namespace EE {
    enum RenderMode {
        NORMAL,
        RASTERIZATION,
        BLINN_PHONG,
        DEPTH,
    };

    struct fragmentPayload {
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec2 uv;
        float depth;
        glm::vec3 worldPos;
        Texture* texture;
    };

    class Renderer {
    public:
        Renderer(Scene* scene, Camera* camera);
        void draw();
        void drawTriangle(Triangle* triangle, glm::vec3 worldPos[3]);
        static bool insideTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
        [[nodiscard]] glm::vec3 getFrame(int x, int y) const { return frameBuffer[getIndex(x,y)] ; };
        [[nodiscard]] int getIndex(int x, int y) const { return x + y * camera->getWidth(); };
        glm::vec3 fragmentShader(const fragmentPayload &payload);
        void setRenderMode(RenderMode m) { renderMode = m; };
        [[nodiscard]] RenderMode getRenderMode() const { return renderMode; };

    private:
        Scene* scene;
        Camera* camera;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        std::vector<float> depthBuffer; // depth buffer stores linear depth from 0 to 1

        std::vector<glm::vec3> frameBuffer;
        RenderMode renderMode = RenderMode::RASTERIZATION;
    };

} // EE

#endif //EDENENGINE_RENDERER_HPP
