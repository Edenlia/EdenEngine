//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_MESH_HPP
#define EDENENGINE_MESH_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Triangle.hpp"
#include "Material/Material.hpp"

namespace EE {

    class Mesh {
    public:
        Mesh();
        ~Mesh();
        [[nodiscard]] std::string getName() const { return name; };
        void setMaterial(Material* m) { this->material = m; };
        [[nodiscard]] Material* getMaterial() const { return material; };
        void setVertices(std::vector<float> v) { this->vertices = v; };
        [[nodiscard]] const std::vector<float>& getVertices() const { return vertices; };
        void setIndices(std::vector<unsigned int> i) { this->indices = i; };
        [[nodiscard]] const std::vector<unsigned int>& getIndices() const { return indices; };
        void setNormals(std::vector<float> n) { this->normals = n; };
        [[nodiscard]] const std::vector<float>& getNormals() const { return normals; };
        void setUVs(std::vector<float> u) { this->uvs = u; };
        [[nodiscard]] const std::vector<float>& getUVs() const { return uvs; };
        void setVerticesNum(unsigned int count) { this->verticesNum = count; };
        [[nodiscard]] unsigned int getVerticesNum() const { return verticesNum; };
        void setIndicesNum(unsigned int count) { this->indicesNum = count; };
        [[nodiscard]] unsigned int getIndicesNum() const { return indicesNum; };
        std::vector<Triangle*> getTriangles();
        void addTriangle(Triangle* triangle) { triangles.push_back(triangle); };

    private:
        std::vector<Triangle*> triangles;
        Material* material = nullptr;
        std::string name;
        unsigned int verticesNum = 0;
        unsigned int indicesNum = 0;
        std::vector<float> vertices; // vertices
        std::vector<float> normals; // normals
        std::vector<float> uvs; // uvs
        std::vector<unsigned int> indices;   // openGL style indices
    };

} // EE

#endif //EDENENGINE_MESH_HPP
