//
// Created by zsy01 on 2023/9/15.
//

#include <string>
#include "Shader.hpp"
#include "Utils/ShaderReader.hpp"

namespace EE {
    void printCompileState(GLuint shader) {
        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE) {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            char *logMessage = new char[logLength];
            glGetShaderInfoLog(shader, logLength, nullptr, logMessage);

            std::cerr << "Shader Compilation Error:\n" << logMessage << std::endl;

            delete[] logMessage;
        }
    }

    void printGLError() {
        GLenum err = glGetError();
        while (err != GL_NO_ERROR) {
            const char* errorStr;

            switch (err) {
                case GL_INVALID_OPERATION:
                    errorStr = "GL_INVALID_OPERATION";
                    break;
                case GL_INVALID_ENUM:
                    errorStr = "GL_INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    errorStr = "GL_INVALID_VALUE";
                    break;
                case GL_OUT_OF_MEMORY:
                    errorStr = "GL_OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    break;
                default:
                    errorStr = "UNKNOWN_ERROR";
                    break;
            }

            std::cerr << "OpenGL Error: " << errorStr << std::endl;

            err = glGetError();
        }
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexShaderStr = ShaderReader::readShader(vertexPath.c_str());
        std::string fragmentShaderStr = ShaderReader::readShader(fragmentPath.c_str());

        const char* vertexShaderSrc = vertexShaderStr.c_str();
        const char* fragmentShaderSrc = fragmentShaderStr.c_str();


        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
        glCompileShader(vertexShader);

        printCompileState(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
        glCompileShader(fragmentShader);

        printCompileState(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

//        GLint success;
//        GLchar infoLog[512];
//        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//
//        if (!success) {
//            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//        }

//        GLint isLinked = 0;
//        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
//        if(isLinked == GL_FALSE) {
//            std::cout << 11111 << std::endl;
//        }

        GLint numUniforms = 0;
        glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);

        for (GLint i = 0; i < numUniforms; i++) {
            char buffer[128];
            GLsizei length = 0;
            GLint size = 0;
            GLenum type = 0;

            glGetActiveUniform(shaderProgram, i, sizeof(buffer), &length, &size, &type, buffer);

            std::cout << "Uniform #" << i << " Type: " << type << " Name: " << buffer << std::endl;
        }

        glUseProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

} // EE