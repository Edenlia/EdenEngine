//
// Created by zsy01 on 2023/9/11.
//

#include <iostream>
#include "Material.hpp"
namespace EE {
    Material::Material() {
        this->name = "";
    }

    glm::vec3 Material::getColor(float u, float v) const {
        glm::vec3 textureValue = albedoMap->getValue(u, v);
        return textureValue;
    }

    glm::vec3 Material::getNormal(float u, float v) const {
        glm::vec3 textureValue = normalMap->getValue(u, v);

        // Tangent space
        textureValue = textureValue / 255.f;
        textureValue = textureValue * 2.f - 1.f;

        return textureValue;
    }

    glm::vec3 Material::getAlbedo(float u, float v) const {
        glm::vec3 textureValue = albedoMap->getValue(u, v);
        textureValue = textureValue / 255.f;
        return textureValue;
    }

    float Material::getMetallic(float u, float v) const {
        float textureValue = metallicMap->getValue(u, v).r;
        textureValue = textureValue / 255.f;
        return textureValue;
    }

    float Material::getRoughness(float u, float v) const {
        float textureValue = roughnessMap->getValue(u, v).r;
        textureValue = textureValue / 255.f;
        return textureValue;
    }
} // EE
