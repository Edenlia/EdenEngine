//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_SOFTWARERENDERER_HPP
#define EDENENGINE_SOFTWARERENDERER_HPP

#include <GL/glew.h>
#include "Renderer.hpp"
#include "Utils/ShaderReader.hpp"
#include "Display/WindowManager.hpp"
#include "Drawer/Drawer.hpp"

namespace EE {
    class SoftwareRenderer : public Renderer {
    public:
        void Initialize(Scene* scene, Camera* camera, WindowManager& windowManager, const std::string &vertexPath, const std::string &fragmentPath) override;
        void Render() override;
        void Shutdown() override;

    private:
        GLuint texture{}; // as render target
        Drawer* drawer{};
    };

} // EE

#endif //EDENENGINE_SOFTWARERENDERER_HPP
