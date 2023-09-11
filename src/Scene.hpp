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
        Scene(){};
        void addObject(EE::Object* newObject) { objects.push_back(newObject); };
        [[nodiscard]] std::vector<EE::Object*> getObjects() const { return objects; };

    private:
        std::vector<EE::Object*> objects;
    };

} // EE

#endif //EDENENGINE_SCENE_HPP
