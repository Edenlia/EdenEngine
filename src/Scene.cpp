//
// Created by zsy01 on 2023/9/7.
//

#include "Scene.hpp"

namespace EE {
    glm::mat4 Scene::getViewPortMatrix() const {
        // left hand coordinate's x axis is right, y axis is up,
        // view port's O in left top corner, x axis is right, y axis is down
        // so we need to flip y axis
        glm::mat4 viewPortMatrix = glm::mat4(1.0f);
        viewPortMatrix = glm::translate(viewPortMatrix, glm::vec3(1.0f, -1.0f, 0.0f));
        viewPortMatrix = glm::scale(viewPortMatrix, glm::vec3(width / 2.0f, height / 2.0f, 1.0f));
        return viewPortMatrix;
    }
} // EE