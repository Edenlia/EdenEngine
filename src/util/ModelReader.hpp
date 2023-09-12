//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_MODELREADER_HPP
#define EDENENGINE_MODELREADER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <map>
#include "Scene.hpp"
#include "Model.hpp"
#include "Texture.hpp"

namespace EE {

    class ModelReader {
    public:
        ModelReader() = default;
        ~ModelReader() = default;
        void readModel(const std::string& path, const std::string& name);
        Model* getModel(const std::string& name) { return this->models[name]; };
        Texture* getTexture(const std::string& name) { return this->textures[name]; };
    private:
        std::map<std::string, Model*> models;
        std::map<std::string, Texture*> textures;

        glm::vec3 defaultColor = glm::vec3(53.0 / 255.0, 33.0 / 255.0, 24.0 / 255.0);
    };

} // EE

#endif //EDENENGINE_MODELREADER_HPP
