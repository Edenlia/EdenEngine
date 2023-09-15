//
// Created by zsy01 on 2023/9/14.
//

#include "ShaderReader.hpp"

namespace EE {
    std::string ShaderReader::readShader(const char *filePath) {
        std::string content;
        std::ifstream fileStream(filePath, std::ios::in);

        if(!fileStream.is_open()) {
            std::cerr << "Could not read shader " << filePath << ". File does not exist." << std::endl;
            return "";
        }

        std::string line = "";
        while(!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }
} // EE