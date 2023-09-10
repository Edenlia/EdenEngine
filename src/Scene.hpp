//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_SCENE_HPP
#define EDENENGINE_SCENE_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Object.hpp"
#include <vector>

namespace EE {

    class Scene {
    public:
        Scene(int width, int height) : width(width), height(height) {};
        void addObject(EE::Object* newObject) { objects.push_back(newObject); };
        [[nodiscard]] std::vector<EE::Object*> getObjects() const { return objects; };
        [[nodiscard]] int getWidth() const { return width; };
        [[nodiscard]] int getHeight() const { return height; };

    private:
        std::vector<EE::Object*> objects;
        int width;
        int height;

    };

} // EE

#endif //EDENENGINE_SCENE_HPP
