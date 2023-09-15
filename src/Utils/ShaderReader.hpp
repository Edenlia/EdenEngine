//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_SHADERREADER_HPP
#define EDENENGINE_SHADERREADER_HPP

#include <string>
#include <fstream>
#include <iostream>

namespace EE {
    class ShaderReader {
    public:
        static std::string readShader(const char* filePath) ;
    };

} // EE

#endif //EDENENGINE_SHADERREADER_HPP
