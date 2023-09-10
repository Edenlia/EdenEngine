//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_OBJECT_HPP
#define EDENENGINE_OBJECT_HPP

#include "glm/glm.hpp"
#include "Triangle.hpp"
#include <vector>

namespace EE {

    class Object {
    public:
        Object();
        Object(std::vector<glm::vec3> vertices, std::vector<int> faces, glm::vec3 color);

        void addTriangle(Triangle* triangle) { triangles.push_back(triangle); };
        [[nodiscard]] std::vector<Triangle*> getTriangles() const { return triangles; };

        // If call for object color, return the first triangle's color
        [[nodiscard]] glm::vec3 getColor() const { return this->triangles[0]->getColor(); };

    private:
        std::vector<Triangle*> triangles;
    };

} // EE

#endif //EDENENGINE_OBJECT_HPP
