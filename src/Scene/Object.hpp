//
// Created by zsy01 on 2023/9/15.
//

#ifndef EDENENGINE_OBJECT_HPP
#define EDENENGINE_OBJECT_HPP

#include "glm/glm.hpp"
#include "Mesh.hpp"
#include "RenderInfo/RenderInfo.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace EE {
    enum RenderMode {
        BLINN_PHONG,
        NORMAL,
        PBR,
        RAY_TRACING
    };

    class Object {
    public:
        Object(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
        [[nodiscard]] glm::vec3 getTranslate() const { return transform[0]; };
        [[nodiscard]] glm::vec3 getRotate() const { return transform[1]; };
        [[nodiscard]] glm::vec3 getScale() const { return transform[2]; };
        void setTransform(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
        [[nodiscard]] glm::mat4 getModelMatrix() const;
        void setRenderMode(RenderMode renderMode) { this->renderMode = renderMode; };
        [[nodiscard]] RenderMode getRenderMode() const { return renderMode; };
        [[nodiscard]] Mesh* getMesh() const { return mesh; };
    protected:
        RenderMode renderMode = BLINN_PHONG;
        glm::vec3 transform[3]{};
        Mesh* mesh = nullptr;
    };

} // EE

#endif //EDENENGINE_OBJECT_HPP
