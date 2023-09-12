//
// Created by zsy01 on 2023/9/12.
//

#ifndef EDENENGINE_LIGHT_HPP
#define EDENENGINE_LIGHT_HPP

#include "glm/glm.hpp"

namespace EE {
    enum LightType {
        POINT_LIGHT,
        DIRECTIONAL_LIGHT,
        SPOT_LIGHT
    };

    class Light {
    public:
        Light(LightType type, glm::vec3 position, glm::vec3 color, float intensity) {
            this->type = type;
            this->position = position;
            this->color = color;
            this->intensity = intensity;
        }

        [[nodiscard]] LightType getType() const { return type; };
        [[nodiscard]] glm::vec3 getPosition() const { return position; };
        [[nodiscard]] glm::vec3 getColor() const { return color; };
        [[nodiscard]] float getIntensity() const { return intensity; };

    private:
        LightType type;
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
    };

    class PointLight : public Light {
    public:
        PointLight(glm::vec3 position, glm::vec3 color, float intensity) : Light(POINT_LIGHT, position, color, intensity) {};
    };

    class DirectionalLight : public Light {
    public:
        DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity) : Light(DIRECTIONAL_LIGHT, glm::vec3(0.0f), color, intensity) {
            this->direction = direction;
        };
        [[nodiscard]] glm::vec3 getDirection() const { return direction; };
    private:
        glm::vec3 direction;
    };

} // EE

#endif //EDENENGINE_LIGHT_HPP
