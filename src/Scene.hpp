//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_SCENE_HPP
#define EDENENGINE_SCENE_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Actor.hpp"
#include <vector>

namespace EE {

    class Scene {
    public:
        Scene(){};
        void addActor(EE::Actor* newActor) { actors.push_back(newActor); };
        [[nodiscard]] std::vector<EE::Actor*> getActors() const { return actors; };

    private:
        std::vector<EE::Actor*> actors;
    };

} // EE

#endif //EDENENGINE_SCENE_HPP
