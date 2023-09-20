//
// Created by zsy01 on 2023/9/15.
//

#include "Object.hpp"
#include "RenderInfo/PhongRenderInfo.hpp"

namespace EE {
    Object::Object(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) {
        this->transform[0] = translate;
        this->transform[1] = rotate;
        this->transform[2] = scale;
    }

    void Object::setTransform(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) {
        transform[0] = translate;
        transform[1] = rotate;
        transform[2] = scale;
    }

    glm::mat4 Object::getModelMatrix() const {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, transform[0]);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::scale(modelMatrix, transform[2]);
        return modelMatrix;
    }
} // EE