//
// Created by zsy01 on 2023/9/7.
//

#ifndef EDENENGINE_CAMERA_HPP
#define EDENENGINE_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace EE {

    class Camera {
    public:
        Camera() = default;
        Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, float fov, float aspect, float zNear, float zFar)
        : position(position), lookAt(lookAt), up(up), fov(fov), aspect(aspect), zNear(zNear), zFar(zFar) {};

        [[nodiscard]] glm::mat4 getViewMatrix() const { return glm::lookAtLH(position, lookAt, up); };
        [[nodiscard]] glm::mat4 getProjectionMatrix() const { return glm::perspectiveLH(glm::radians(fov), aspect, zNear, zFar); };
        [[nodiscard]] float getNearPlane() const { return zNear; };
        [[nodiscard]] float getFarPlane() const { return zFar; };
        [[nodiscard]] int getWidth() const { return width; };
        [[nodiscard]] int getHeight() const { return height; };
        void setWidth(int w) { this->width = w; };
        void setHeight(int h) { this->height = h; };
        [[nodiscard]] glm::vec3 getPosition() const { return position; };
        [[nodiscard]] glm::vec3 getLookAt() const { return lookAt; };
        [[nodiscard]] glm::vec3 getUp() const { return up; };
        [[nodiscard]] float getMoveSpeed() const { return moveSpeed; };
        void setPosition(glm::vec3 pos) { this->position = pos; };
        void setDeltaTime(float dt) { this->deltaTime = dt; };
        [[nodiscard]] float getDeltaTime() const { return deltaTime; };


    private:
        glm::vec3 position;
        glm::vec3 lookAt;
        glm::vec3 up;

        float fov;
        float aspect;
        float zNear;
        float zFar;
        int width;
        int height;
        float moveSpeed = 10;
        float deltaTime = 0.0f;

    };

} // EE

#endif //EDENENGINE_CAMERA_HPP
