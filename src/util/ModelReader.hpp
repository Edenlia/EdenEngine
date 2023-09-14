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
#include "Material.hpp"

namespace EE {
    enum ModelFormat {
        OBJ,
        DAE,
        DEFAULT,
    };

    class ModelReader {
    public:
        ModelReader() = default;
        ~ModelReader() = default;
        void readModel(const std::string &dirPath, const std::string& name, const std::string &extension);
        void readMaterial(const std::string &dirPath, const std::string &modelName, const std::string &materialIndexName);
        Model* getModel(const std::string& name) { return this->models[name]; };
        Material* getMaterial(const std::string& name) { return this->materials[name]; };
    private:
        std::map<std::string, Model*> models;
        std::map<std::string, Material*> materials;

        glm::vec3 defaultColor = glm::vec3(53.0, 33.0, 24.0);
    };

} // EE

#endif //EDENENGINE_MODELREADER_HPP
