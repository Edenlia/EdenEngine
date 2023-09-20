//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_PHONGDRAWER_HPP
#define EDENENGINE_PHONGDRAWER_HPP

#include <glm/vec2.hpp>
#include "Drawer.hpp"
#include "Material/Material.hpp"
#include "Scene/Triangle.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

namespace EE {

    class PhongDrawer : public Drawer {
    public:
        enum DrawMode {
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
            Material* material;
        };

        PhongDrawer(int width, int height, int channel, Scene *scene, Camera *camera);

        void draw(std::vector<unsigned char>& buffer) override;
        void drawTriangle(Triangle* screenTriangle, glm::vec3 worldPos[3], std::vector<unsigned char>& buffer);
        [[nodiscard]] int getIndex(int x, int y) const { return x + y * camera->getWidth(); };
        static bool insideTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
        glm::vec3 drawColor(const fragmentPayload &payload);
        void setDrawMode(DrawMode m) { drawMode = m; };


    private:
        Scene* scene;
        Camera* camera;

        glm::mat4 viewMatrix = glm::mat4(1.f);
        glm::mat4 projectionMatrix = glm::mat4(1.f);
        std::vector<float> depthBuffer; // depth buffer stores linear depth from 0 to 1

        DrawMode drawMode = DrawMode::BLINN_PHONG;
    };

} // EE

#endif //EDENENGINE_PHONGDRAWER_HPP
