//
// Created by zsy01 on 2023/9/9.
//

#ifndef EDENENGINE_EEMATH_HPP
#define EDENENGINE_EEMATH_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <tuple>

namespace EE {
    static std::tuple<float, float, float> computeBarycentric2D(float x, float y, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) {
        float c1 = (x * (p1.y - p2.y) + y * (p2.x - p1.x) + p1.x * p2.y - p2.x * p1.y) /
                (p0.x * (p1.y - p2.y) + p0.y * (p2.x - p1.x) + p1.x * p2.y - p2.x * p1.y);
        float c2 = (x * (p2.y - p0.y) + y * (p0.x - p2.x) + p2.x * p0.y - p0.x * p2.y) /
                (p1.x * (p2.y - p0.y) + p1.y * (p0.x - p2.x) + p2.x * p0.y - p0.x * p2.y);
        float c3 = (x * (p0.y - p1.y) + y * (p1.x - p0.x) + p0.x * p1.y - p1.x * p0.y) /
                (p2.x * (p0.y - p1.y) + p2.y * (p1.x - p0.x) + p0.x * p1.y - p1.x * p0.y);

        return {c1, c2, c3};
    }

} // EE

#endif //EDENENGINE_EEMATH_HPP
