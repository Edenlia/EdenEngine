//
// Created by zsy01 on 2023/9/8.
//

#ifndef EDENENGINE_RENDERER_HPP
#define EDENENGINE_RENDERER_HPP

#include <GL/glew.h>
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Material.hpp"
#include "Display/WindowManager.hpp"
#include <iostream>

namespace EE {
    class Renderer {
    public:
        virtual void Initialize(Scene* scene, Camera* camera, WindowManager& windowManager, const std::string &vertexPath, const std::string &fragmentPath) = 0;
        virtual void Render() = 0;
        virtual void Shutdown() = 0;

    protected:
        GLuint loadShader(const std::string& vertexPath, const std::string& fragmentPath);

        GLuint shaderProgram;
        GLuint VAO, VBO, EBO;
        WindowManager* windowManager;
        Scene* scene;
        Camera* camera;
        std::vector<unsigned char> buffer;
    };

} // EE

#endif //EDENENGINE_RENDERER_HPP
