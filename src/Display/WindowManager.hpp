//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_WINDOWMANAGER_HPP
#define EDENENGINE_WINDOWMANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Scene/Camera.hpp"

namespace EE {

    class WindowManager {
    public:
        WindowManager(int width, int height, const char *title, Camera *camera);

        ~WindowManager() {
            glfwTerminate();
        }

        [[nodiscard]] GLFWwindow* getWindow() const {return window;}

        [[nodiscard]] bool shouldClose() const {return glfwWindowShouldClose(window);}

        static void pollEvents() {glfwPollEvents();}

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        [[nodiscard]] float getDeltaTime() const {return deltaTime;}

        void swapBuffers();

        [[nodiscard]] int getWidth() const {return width;}
        [[nodiscard]] int getHeight() const {return height;}

    private:
        GLFWwindow* window;
        int width;
        int height;
        Camera* camera;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    };

} // EE

#endif //EDENENGINE_WINDOWMANAGER_HPP
