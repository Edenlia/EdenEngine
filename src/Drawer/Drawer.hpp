//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_DRAWER_HPP
#define EDENENGINE_DRAWER_HPP

#include <glm/vec3.hpp>
#include <vector>

namespace EE {

    class Drawer {
    public:
        Drawer(int width, int height, int channel) : width(width), height(height), channel(channel) {}

        virtual void draw(std::vector<unsigned char>& buffer) = 0;

    protected:
        int width;
        int height;
        int channel;
    };

} // EE

#endif //EDENENGINE_DRAWER_HPP
