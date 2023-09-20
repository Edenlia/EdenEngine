//
// Created by zsy01 on 2023/9/14.
//

#include "WindowManager.hpp"
#include "Scene/Camera.hpp"

namespace EE {
    WindowManager::WindowManager(int width, int height, const char *title, Camera *camera) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        this->width = width;
        this->height = height;
        this->camera = camera;
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(-1);
        }

        glfwSetWindowUserPointer(window, camera);
        glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);
        glewInit();

    }



    void WindowManager::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_W) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 toward = glm::normalize(camera->getLookAt());
            camera->setPosition(cameraPos + toward * camera->getMoveSpeed() * camera->getDeltaTime());
        } else if (key == GLFW_KEY_S) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 toward = -glm::normalize(camera->getLookAt());
            camera->setPosition(cameraPos + toward * camera->getMoveSpeed() * camera->getDeltaTime());
        } else if (key == GLFW_KEY_A) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 right = glm::normalize(glm::cross(camera->getLookAt(), camera->getUp()));
            camera->setPosition(cameraPos + right * camera->getMoveSpeed() * camera->getDeltaTime());
        } else if (key == GLFW_KEY_D) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 right = -glm::normalize(glm::cross(camera->getLookAt(), camera->getUp()));
            camera->setPosition(cameraPos + right * camera->getMoveSpeed() * camera->getDeltaTime());
        } else if (key == GLFW_KEY_Q) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 up = glm::normalize(camera->getUp());
            camera->setPosition(cameraPos + up * camera->getMoveSpeed() * camera->getDeltaTime());
        } else if (key == GLFW_KEY_E) {
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 up = -glm::normalize(camera->getUp());
            camera->setPosition(cameraPos + up * camera->getMoveSpeed() * camera->getDeltaTime());
        }
    }

    void WindowManager::swapBuffers() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(window);
    }
} // EE