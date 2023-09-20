//
// Created by zsy01 on 2023/9/15.
//

#ifndef EDENENGINE_SHADER_HPP
#define EDENENGINE_SHADER_HPP

#include <GL/glew.h>
#include <string>

namespace EE {

    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        GLuint shaderProgram;
    };

} // EE

#endif //EDENENGINE_SHADER_HPP
