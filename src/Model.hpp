//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_MODEL_HPP
#define EDENENGINE_MODEL_HPP

#include <string>
#include <vector>
#include "Triangle.hpp"

namespace EE {

    class Model {
    public:
        Model();
        void addTriangle(Triangle* triangle) { triangles.push_back(triangle); };
        [[nodiscard]] std::vector<Triangle*> getTriangles() const { return triangles; };
        [[nodiscard]] std::string getName() const { return name; };
    private:
        std::vector<Triangle*> triangles;
        std::string name;
    };

} // EE

#endif //EDENENGINE_MODEL_HPP
