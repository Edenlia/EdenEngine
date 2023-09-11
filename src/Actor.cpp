//
// Created by zsy01 on 2023/9/7.
//

#include "Actor.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace EE {
    Actor::Actor(Model* m, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) {
        this->model = m;
        this->transform[0] = translate;
        this->transform[1] = rotate;
        this->transform[2] = scale;
    }

    void Actor::setTransform(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) {
        transform[0] = translate;
        transform[1] = rotate;
        transform[2] = scale;
    }

    glm::mat4 Actor::getModelMatrix() const {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, transform[0]);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform[1].z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::scale(modelMatrix, transform[2]);
//        std::cout << "Model Matrix: " << modelMatrix[0][0] << " " << modelMatrix[0][1] << " " << modelMatrix[0][2] << " " << modelMatrix[0][3] << std::endl;
//        std::cout << "Model Matrix: " << modelMatrix[1][0] << " " << modelMatrix[1][1] << " " << modelMatrix[1][2] << " " << modelMatrix[1][3] << std::endl;
//        std::cout << "Model Matrix: " << modelMatrix[2][0] << " " << modelMatrix[2][1] << " " << modelMatrix[2][2] << " " << modelMatrix[2][3] << std::endl;
//        std::cout << "Model Matrix: " << modelMatrix[3][0] << " " << modelMatrix[3][1] << " " << modelMatrix[3][2] << " " << modelMatrix[3][3] << std::endl;
//        std::cout << std::endl;
        return modelMatrix;
    }
} // EE