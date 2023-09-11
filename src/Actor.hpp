//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_ACTOR_HPP
#define EDENENGINE_ACTOR_HPP

#include "glm/glm.hpp"
#include "Triangle.hpp"
#include "Model.hpp"
#include <vector>

namespace EE {

    class Actor {
    public:
        Actor(Model* m, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);

        void addTriangle(Triangle* triangle) { triangles.push_back(triangle); };
        [[nodiscard]] std::vector<Triangle*> getTriangles() const { return triangles; };
        [[nodiscard]] glm::mat4 getModelMatrix() const;
        void setTransform(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
        [[nodiscard]] glm::vec3 getTranslate() const { return transform[0]; };
        [[nodiscard]] glm::vec3 getRotate() const { return transform[1]; };
        [[nodiscard]] glm::vec3 getScale() const { return transform[2]; };
        [[nodiscard]] Model* getModel() const { return model; };

    private:
        std::vector<Triangle*> triangles;
        glm::vec3 transform[3];
        Model* model;
    };

} // EE

#endif //EDENENGINE_ACTOR_HPP
