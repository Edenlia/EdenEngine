//
// Created by zsy01 on 2023/9/11.
//

#include "MeshReader.hpp"
#include <iostream>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb/stb_image.h"

namespace EE {
    void MeshReader::readModel(const std::string &dirPath, const std::string& name, const std::string &extension) {
        Assimp::Importer importer;

        std::string modelPath = dirPath + name + '.' + extension;

        const aiScene *as = importer.ReadFile(modelPath,
                                              aiProcess_Triangulate |
                                              aiProcess_JoinIdenticalVertices |
                                              aiProcess_GenSmoothNormals |
                                              aiProcess_FlipUVs
        );

        if (!as || as->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !as->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            exit(-1);
        }

        for (int i = 0; i < as->mNumMeshes; i++) {
            aiMesh *aMesh = as->mMeshes[i];
            aiMaterial *aMaterial = as->mMaterials[aMesh->mMaterialIndex];
            std::string materialIndexName = aMaterial->GetName().C_Str();
            readMaterial(dirPath + "textures/", name, materialIndexName);

            std::string materialName = name + "_" + materialIndexName;

            Material *m = materials[materialName];

            assert(aMesh->HasNormals());
            auto* model = new Mesh();
            for (int j = 0; j < aMesh->mNumFaces; j++) {
                aiFace face = aMesh->mFaces[j];
                auto *triangle = new Triangle();

                assert(face.mNumIndices == 3);
                for (int k = 0; k < face.mNumIndices; k++) {
                    int index = face.mIndices[k];
                    aiVector3D vertex = aMesh->mVertices[index];
                    aiColor4D color;
                    if (!aMesh->HasVertexColors(0)) {
                        color = aiColor4D(defaultColor.x, defaultColor.y, defaultColor.z, 1.0f);
                    } else {
                        color = aMesh->mColors[0][index];
                    }
                    aiVector3D genNormal = aMesh->mNormals[index];
//                std::cout << "genNormal: " << genNormal.x << " " << genNormal.y << " " << genNormal.z << std::endl;

                    triangle->setVertex(k, glm::vec3(vertex.x, vertex.y, vertex.z));
                    triangle->setColor(k, glm::vec3(color.r, color.g, color.b));
                    triangle->setNormal(k, glm::vec3(genNormal.x, genNormal.y, genNormal.z));
                    aiVector3D uv = aMesh->mTextureCoords[0][index];
                    triangle->setUV(k, glm::vec2(uv.x, uv.y));
//                    std::cout << "uv: " << uv.x << " " << uv.y << std::endl;
                    triangle->setMaterial(m);
                }
                model->addTriangle(triangle);
            }
            models[name] = model;
        }
    }

    void MeshReader::readMaterial(const std::string &dirPath, const std::string &modelName, const std::string &materialIndexName) {
        auto* newMaterial = new Material();

        newMaterial->setName(modelName + "_" + materialIndexName);

        // read albedo, metallic, roughness, normal maps
        int width, height, channels;

        // albedo
        std::string albedoPath = dirPath + materialIndexName + "_albedo.jpg";
        unsigned char* data = stbi_load(albedoPath.c_str(), &width, &height, &channels, 0);
        if (data) {
            newMaterial->setAlbedoMap(std::make_shared<Texture>(channels, width, height, data));
        } else {
            std::cout << "No albedo map for " << modelName << std::endl;
            std::cerr << "ERROR::STB::" << stbi_failure_reason() << std::endl;
        }

        // normal
        std::string normalPath = dirPath + materialIndexName + "_normal.png";
        data = stbi_load(normalPath.c_str(), &width, &height, &channels, 3);
        if (data) {
            newMaterial->setNormalMap(std::make_shared<Texture>(channels, width, height, data));
        } else {
            std::cout << "No normal map for " << modelName << std::endl;
            std::cerr << "ERROR::STB::" << stbi_failure_reason() << std::endl;
        }

        // roughness
        std::string roughnessPath = dirPath + materialIndexName + "_roughness.jpg";
        data = stbi_load(roughnessPath.c_str(), &width, &height, &channels, 0);
        if (data) {
            newMaterial->setRoughnessMap(std::make_shared<Texture>(channels, width, height, data));
        } else {
            std::cout << "No roughness map for " << modelName << std::endl;
            std::cerr << "ERROR::STB::" << stbi_failure_reason() << std::endl;
        }

        // metallic
        std::string metallicPath = dirPath + materialIndexName + "_metallic.jpg";
        data = stbi_load(metallicPath.c_str(), &width, &height, &channels, 0);
        if (data) {
            newMaterial->setMetallicMap(std::make_shared<Texture>(channels, width, height, data));
        } else {
            std::cout << "No metallic map for " << modelName << std::endl;
            std::cerr << "ERROR::STB::" << stbi_failure_reason() << std::endl;
        }

        materials[newMaterial->getName()] = newMaterial;

    }
} // EE