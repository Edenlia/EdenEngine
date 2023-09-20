//
// Created by zsy01 on 2023/9/11.
//

#ifndef EDENENGINE_MATERIAL_HPP
#define EDENENGINE_MATERIAL_HPP

#include <memory>
#include <utility>
#include <string>
#include "glm/glm.hpp"
#include "Texture.hpp"

namespace EE {

    class Material {
    public:
        Material();
        void setName(std::string n) { this->name = std::move(n); };
        void setAlbedoMap(std::shared_ptr<Texture> texture) { this->albedoMap = std::move(texture); };
        void setNormalMap(std::shared_ptr<Texture> texture) { this->normalMap = std::move(texture); };
        void setMetallicMap(std::shared_ptr<Texture> texture) { this->metallicMap = std::move(texture); };
        void setRoughnessMap(std::shared_ptr<Texture> texture) { this->roughnessMap = std::move(texture); };
        [[nodiscard]] std::shared_ptr<Texture> getAlbedoMap() const { return this->albedoMap; };
        [[nodiscard]] std::shared_ptr<Texture> getNormalMap() const { return this->normalMap; };
        [[nodiscard]] std::shared_ptr<Texture> getMetallicMap() const { return this->metallicMap; };
        [[nodiscard]] std::shared_ptr<Texture> getRoughnessMap() const { return this->roughnessMap; };
        [[nodiscard]] std::string getName() const { return this->name; };
        [[nodiscard]] glm::vec3 getNormal(float u, float v) const;
        [[nodiscard]] glm::vec3 getColor(float u, float v) const;
        [[nodiscard]] glm::vec3 getAlbedo(float u, float v) const;
        [[nodiscard]] float getMetallic(float u, float v) const;
        [[nodiscard]] float getRoughness(float u, float v) const;

    private:
        std::string name;
        std::shared_ptr<Texture> normalMap = nullptr;
        std::shared_ptr<Texture> albedoMap = nullptr;
        std::shared_ptr<Texture> metallicMap = nullptr;
        std::shared_ptr<Texture> roughnessMap = nullptr;
    };

} // EE

#endif //EDENENGINE_MATERIAL_HPP
