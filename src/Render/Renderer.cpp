//
// Created by zsy01 on 2023/9/8.
//

#include "Renderer.hpp"
#include "Utils/EEMath.hpp"
#include "Utils/ShaderReader.hpp"
#include <limits>
#include <array>

namespace EE {

    GLuint Renderer::loadShader(const std::string &vertexPath, const std::string &fragmentPath) {
        std::string vertexShaderStr = ShaderReader::readShader(vertexPath.c_str());
        std::string fragmentShaderStr = ShaderReader::readShader(fragmentPath.c_str());

        const char* vertexShaderSrc = vertexShaderStr.c_str();
        const char* fragmentShaderSrc = fragmentShaderStr.c_str();


        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
        glCompileShader(fragmentShader);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }
} // EE