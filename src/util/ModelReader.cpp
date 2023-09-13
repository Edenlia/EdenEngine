//
// Created by zsy01 on 2023/9/11.
//

#include "ModelReader.hpp"
#include <iostream>
#include <glm/glm.hpp>

namespace EE {
    void ModelReader::readModel(const std::string &path, const std::string& name) {
        Assimp::Importer importer;

        const aiScene *as = importer.ReadFile(path,
                                              aiProcess_Triangulate |
                                              aiProcess_JoinIdenticalVertices |
                                              aiProcess_GenSmoothNormals
        );

        if (!as || as->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !as->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            exit(-1);
        }

        for (int i = 0; i < as->mNumMeshes; i++) {
            aiMesh *mesh = as->mMeshes[i];
            aiMaterial *material = as->mMaterials[mesh->mMaterialIndex];

            
            if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
                aiString str;
                material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
                std::cout << "texture: " << str.C_Str() << std::endl;
            }
            assert(mesh->HasNormals());
            auto* model = new Model();
            for (int j = 0; j < mesh->mNumFaces; j++) {
                aiFace face = mesh->mFaces[j];
                auto *triangle = new Triangle();
                assert(face.mNumIndices == 3);
                for (int k = 0; k < face.mNumIndices; k++) {
                    int index = face.mIndices[k];
                    aiVector3D vertex = mesh->mVertices[index];
                    aiColor4D color;
                    if (!mesh->HasVertexColors(0)) {
                        color = aiColor4D(defaultColor.x, defaultColor.y, defaultColor.z, 1.0f);
                    } else {
                        color = mesh->mColors[0][index];
                    }
                    aiVector3D normal = mesh->mNormals[index];
//                std::cout << "normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;

                    triangle->setVertex(k, glm::vec3(vertex.x, vertex.y, vertex.z));
                    triangle->setColor(k, glm::vec3(color.r, color.g, color.b));
                    triangle->setNormal(k, glm::vec3(normal.x, normal.y, normal.z));
                }
                model->addTriangle(triangle);
            }
            models[name] = model;
        }
    }

    ModelFormat ModelReader::getFileFormat(const std::string &filename) {
        {
            size_t pos = filename.find_last_of('.');
            if (pos == std::string::npos) {
                return DEFAULT;
            }
            if (filename.substr(pos + 1) == "obj")
                return OBJ;
            else if (filename.substr(pos + 1) == "dae")
                return DAE;
            else
                return DEFAULT;
        }
    }

    void ModelReader::readDaeModel(const std::string &path, const std::string &name) {

    }

    void ModelReader::readObjModel(const std::string &path, const std::string &name) {

    }
} // EE