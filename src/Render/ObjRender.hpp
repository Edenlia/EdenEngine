//
// Created by zsy01 on 2023/9/15.
//

#ifndef EDENENGINE_OBJRENDER_HPP
#define EDENENGINE_OBJRENDER_HPP

#include <vector>
#include "Shader/Shader.hpp"
#include "Scene/Object.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"
#include "RenderInfo/RenderInfo.hpp"

namespace EE {
    class ObjRender {
    public:
        ObjRender(Object* object, RenderInfo* renderInfo);

        void bindGeometryInfo();
        void bindMaterialInfo();
        void bindCameraInfo(Camera* camera);
        GLuint loadTexture(const std::shared_ptr<Texture> &texture, const std::string &name, int index);
        void bindUniformData(GLSLData& data);

        void render(Camera* camera);

        void shutdown() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &positionVBO);
            glDeleteBuffers(1, &normalVBO);
            glDeleteBuffers(1, &texcoordVBO);
            glDeleteBuffers(1, &EBO);
            glDeleteProgram(shader->shaderProgram);
        }

    private:
        GLuint VAO{}, positionVBO{}, normalVBO{}, texcoordVBO{}, EBO{};
        GLuint textureID1{}, textureID2{};
        Shader* shader;
        Object* object;
        RenderInfo* renderInfo{};
    };




} // EE

#endif //EDENENGINE_OBJRENDER_HPP
