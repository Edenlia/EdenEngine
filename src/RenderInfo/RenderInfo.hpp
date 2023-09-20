//
// Created by zsy01 on 2023/9/16.
//

#ifndef EDENENGINE_RENDERINFO_HPP
#define EDENENGINE_RENDERINFO_HPP

#include <iostream>
#include <variant>
#include <vector>
#include <glm/glm.hpp>

namespace EE {
    using GLSLValue = std::variant<float, glm::vec2, glm::vec3, glm::vec4, glm::mat4, unsigned char*>;

    enum GLSLDataType {
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT4,
    };

    struct GLSLData {
        std::string name;
        GLSLDataType type;
        GLSLValue value;
    };

    class RenderInfo {
    public:
        RenderInfo(const std::string& vertexShader, const std::string& fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader) {};

        void addUniformData(const GLSLData& data) { this->glslUniformData.push_back(data); };
        void addInputData(const GLSLData& data) { this->glslInputData.push_back(data); };

        std::vector<GLSLData> glslUniformData;
        std::vector<GLSLData> glslInputData;
        std::string vertexShader;
        std::string fragmentShader;
    };

} // EE

#endif //EDENENGINE_RENDERINFO_HPP
