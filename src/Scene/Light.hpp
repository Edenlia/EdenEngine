//
// Created by zsy01 on 2023/9/12.
//

#ifndef EDENENGINE_LIGHT_HPP
#define EDENENGINE_LIGHT_HPP

#include "glm/glm.hpp"
#include "Object.hpp"

namespace EE {
    enum LightType {
        POINT_LIGHT,
        DIRECTIONAL_LIGHT,
        SPOT_LIGHT
    };

    class Light : public Object {
    public:
        Light(LightType type, glm::vec3 color, float intensity, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) : Object(translate, rotate, scale) {
            this->type = type;
            this->color = color;
            this->intensity = intensity;
        }

        [[nodiscard]] LightType getType() const { return type; };
        [[nodiscard]] glm::vec3 getColor() const { return color; };
        [[nodiscard]] float getIntensity() const { return intensity; };

    protected:
        LightType type;
        glm::vec3 color;
        float intensity;
    };

    class PointLight : public Light {
    public:
        PointLight(glm::vec3 color, float intensity, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) : Light(POINT_LIGHT, color, intensity, translate, rotate, scale) {};
    };

    class DirectionalLight : public Light {
    public:
        DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) : Light(DIRECTIONAL_LIGHT, color, intensity, translate, rotate, scale) {
            this->direction = direction;
        };
        [[nodiscard]] glm::vec3 getDirection() const { return direction; };
    private:
        glm::vec3 direction{};
    };

} // EE

#endif //EDENENGINE_LIGHT_HPP
