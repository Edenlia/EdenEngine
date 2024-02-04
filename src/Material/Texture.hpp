//
// Created by 章书飏 on 2023/9/13.
//

#ifndef EDENENGINE_TEXTURE_HPP
#define EDENENGINE_TEXTURE_HPP

#include <glm/vec3.hpp>

namespace EE {

    class Texture {
    public:
        Texture(int channel, int width, int height, unsigned char* raw_data)
        : channel(channel), width(width), height(height), raw_data(raw_data) {};

        int channel;
        int width;
        int height;
        unsigned char* raw_data;

        glm::vec3 getValue(float u, float v) const;
    };

} // EE

#endif //EDENENGINE_TEXTURE_HPP
