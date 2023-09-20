//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_ACTOR_HPP
#define EDENENGINE_ACTOR_HPP

#include "glm/glm.hpp"
#include "Scene/Triangle.hpp"
#include "Scene/Mesh.hpp"
#include "Object.hpp"
#include <vector>

namespace EE {

    class Actor : public Object {
    public:
        Actor(Mesh *m, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
    };

} // EE

#endif //EDENENGINE_ACTOR_HPP
