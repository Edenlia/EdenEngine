//
// Created by zsy01 on 2023/9/7.
//

#include "Actor.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {
    Actor::Actor(Mesh *m, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) : Object(translate, rotate, scale) {
        this->mesh = m;
    }
} // EE