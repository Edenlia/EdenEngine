//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_TEXTURE_HPP
#define EDENENGINE_TEXTURE_HPP

#include "glm/glm.hpp"

namespace EE {

    class Texture {
    public:
        Texture();
        [[nodiscard]] glm::vec3 getColor(float u, float v) const;
    private:

    };

} // EE

#endif //EDENENGINE_TEXTURE_HPP
