//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_TRIANGLE_HPP
#define EDENENGINE_TRIANGLE_HPP

#include "glm/glm.hpp"
#include <array>

namespace EE {

    class Triangle {
    public:
        Triangle();

        glm::vec4 vertices[3]{};
        glm::vec3 normal[3]{};
        glm::vec3 color[3]{};
        glm::vec2 uv[3]{};



        void setColor(int i, glm::vec3 clr) { this->color[i] = clr; };
        void setNormal(int i, glm::vec3 n) { this->normal[i] = n; };
        void setVertex(int i, glm::vec4 v) { this->vertices[i] = v; };
        void setVertex(int i, glm::vec3 v) { this->vertices[i] = glm::vec4(v, 1.f); };
        [[nodiscard]] glm::vec3 getColor(int i) const { return color[i]; };
        [[nodiscard]] glm::vec3 getNormal(int i) const { return normal[i]; };
        [[nodiscard]] glm::vec4 getVertex(int i) const { return vertices[i]; };

        // If call for triangle color, return the first vertex's color
        [[nodiscard]] glm::vec3 getColor() const { return color[0]; };

        [[nodiscard]] std::array<glm::vec4, 3> ToVector4();
    };

} // EE

#endif //EDENENGINE_TRIANGLE_HPP
