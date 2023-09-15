//
// Created by zsy01 on 2023/9/7.
//

#include "Triangle.hpp"
#include <algorithm>

namespace EE {
    Triangle::Triangle() {
        this->vertices[0] = glm::vec4(0.f, 0.f, 0.f, 1.f);
        this->vertices[1] = glm::vec4(0.f, 0.f, 0.f, 1.f);
        this->vertices[2] = glm::vec4(0.f, 0.f, 0.f, 1.f);

        this->normal[0] = glm::vec3(0.f, 0.f, 0.f);
        this->normal[1] = glm::vec3(0.f, 0.f, 0.f);
        this->normal[2] = glm::vec3(0.f, 0.f, 0.f);

        this->color[0] = glm::vec3(0.f, 0.f, 0.f);
        this->color[1] = glm::vec3(0.f, 0.f, 0.f);
        this->color[2] = glm::vec3(0.f, 0.f, 0.f);
    }
} // EE