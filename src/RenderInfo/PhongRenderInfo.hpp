//
// Created by zsy01 on 2023/9/16.
//

#ifndef EDENENGINE_PHONGRENDERINFO_HPP
#define EDENENGINE_PHONGRENDERINFO_HPP

#include "RenderInfo.hpp"
#include "Scene/Light.hpp"
#include "glm/glm.hpp"

namespace EE {

    class PhongRenderInfo : public RenderInfo {
    public:
        PhongRenderInfo(const Light *light, glm::mat4 modelMatrix, const std::string &vertexShader,
                        const std::string &fragmentShader);
    };
} // EE

#endif //EDENENGINE_PHONGRENDERINFO_HPP
