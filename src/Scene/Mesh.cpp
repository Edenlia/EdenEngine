//
// Created by zsy01 on 2023/9/11.
//

#include <iostream>
#include "Mesh.hpp"

namespace EE {
    Mesh::Mesh(){
        this->triangles = std::vector<Triangle*>(0);
    }

    Mesh::~Mesh() {
        delete this->material;
    }

    std::vector<Triangle *> Mesh::getTriangles() {
        if (this->triangles.empty()) {
            for (int i = 0; i < this->indicesNum; i += 3) {
                auto* triangle = new Triangle();
                triangle->setMaterial(this->material);
                unsigned int i1 = this->indices[i];
                unsigned int i2 = this->indices[i + 1];
                unsigned int i3 = this->indices[i + 2];
                glm::vec3 v1 = glm::vec3(this->vertices[i1 * 3], this->vertices[i1 * 3 + 1], this->vertices[i1 * 3 + 2]);
                glm::vec3 v2 = glm::vec3(this->vertices[i2 * 3], this->vertices[i2 * 3 + 1], this->vertices[i2 * 3 + 2]);
                glm::vec3 v3 = glm::vec3(this->vertices[i3 * 3], this->vertices[i3 * 3 + 1], this->vertices[i3 * 3 + 2]);
                glm::vec3 n1 = glm::vec3(this->normals[i1 * 3], this->normals[i1 * 3 + 1], this->normals[i1 * 3 + 2]);
                glm::vec3 n2 = glm::vec3(this->normals[i2 * 3], this->normals[i2 * 3 + 1], this->normals[i2 * 3 + 2]);
                glm::vec3 n3 = glm::vec3(this->normals[i3 * 3], this->normals[i3 * 3 + 1], this->normals[i3 * 3 + 2]);
                glm::vec2 uv1 = glm::vec2(this->uvs[i1 * 2], this->uvs[i1 * 2 + 1]);
                glm::vec2 uv2 = glm::vec2(this->uvs[i2 * 2], this->uvs[i2 * 2 + 1]);
                glm::vec2 uv3 = glm::vec2(this->uvs[i3 * 2], this->uvs[i3 * 2 + 1]);

                triangle->setVertex(0, glm::vec4(v1, 1.f));
                triangle->setVertex(1, glm::vec4(v2, 1.f));
                triangle->setVertex(2, glm::vec4(v3, 1.f));
                triangle->setNormal(0, n1);
                triangle->setNormal(1, n2);
                triangle->setNormal(2, n3);
                triangle->setUV(0, uv1);
                triangle->setUV(1, uv2);
                triangle->setUV(2, uv3);

                triangles.push_back(triangle);
            }
        }

        return triangles;
    }
} // EE