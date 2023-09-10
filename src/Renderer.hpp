//
// Created by zsy01 on 2023/9/8.
//

#ifndef EDENENGINE_RENDERER_HPP
#define EDENENGINE_RENDERER_HPP

#include "Scene.hpp"
#include "Camera.hpp"
#include <iostream>


namespace EE {

    class Renderer {
    public:
        Renderer(Scene* scene, Camera* camera);
        void draw();
        void drawTriangle(Triangle* triangle);
        static bool insideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
        [[nodiscard]] glm::vec3 getFrame(int x, int y) const { return frameBuffer[y + x * scene->getWidth()] ; };

    private:
        Scene* scene;
        Camera* camera;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        std::vector<float> depthBuffer;

        std::vector<glm::vec3> frameBuffer;
    };

} // EE

#endif //EDENENGINE_RENDERER_HPP
