//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_MATERIAL_HPP
#define EDENENGINE_MATERIAL_HPP

#include "glm/glm.hpp"

namespace EE {

    class Material {
    public:
        Material();
        [[nodiscard]] glm::vec3 getColor(float u, float v) const;
    private:

    };

} // EE

#endif //EDENENGINE_MATERIAL_HPP
