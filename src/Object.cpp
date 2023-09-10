//
// Created by zsy01 on 2023/9/7.
//

#include "Object.hpp"

namespace EE {
    Object::Object() {
        this->triangles = std::vector<Triangle*>();
    }

    Object::Object(std::vector<glm::vec3> vertices, std::vector<int> faces, glm::vec3 color) {

        for (int i = 0; i < faces.size(); i += 3) {
            auto* triangle = new Triangle();
            triangle->setVertex(0, vertices[faces[i]]);
            triangle->setVertex(1, vertices[faces[i + 1]]);
            triangle->setVertex(2, vertices[faces[i + 2]]);
            triangle->setColor(0, color);
            triangle->setColor(1, color);
            triangle->setColor(2, color);
            triangles.push_back(triangle);
        }
    }
} // EE