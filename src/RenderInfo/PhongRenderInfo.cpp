//
// Created by zsy01 on 2023/9/16.
//

#include "PhongRenderInfo.hpp"

namespace EE {
    PhongRenderInfo::PhongRenderInfo(const Light *light, glm::mat4 modelMatrix, const std::string &vertexShader,
                                     const std::string &fragmentShader) : RenderInfo(vertexShader, fragmentShader) {
        glslUniformData = std::vector<GLSLData>{
                GLSLData("uModel", GLSLDataType::MAT4, modelMatrix),
                GLSLData("uLightPos", GLSLDataType::VEC3, light->getTranslate()),
                GLSLData("uLightIntensity", GLSLDataType::VEC3, light->getColor() * light->getIntensity()),
        };
    }
} // EE