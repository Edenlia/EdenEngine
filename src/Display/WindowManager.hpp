//
// Created by zsy01 on 2023/9/14.
//

#ifndef EDENENGINE_WINDOWMANAGER_HPP
#define EDENENGINE_WINDOWMANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace EE {

    class WindowManager {
        WindowManager(int width, int height, const char* title) {
            if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW" << std::endl;
                exit(-1);
            }

            window = glfwCreateWindow(width, height, title, NULL, NULL);
            if (!window) {
                glfwTerminate();
                exit(-1);
            }

            glfwMakeContextCurrent(window);
            glewInit();
        }

        ~WindowManager() {
            glfwTerminate();
        }

        [[nodiscard]] GLFWwindow* getWindow() const {return window;}

        [[nodiscard]] bool shouldClose() const {return glfwWindowShouldClose(window);}

        void pollEvents() const {glfwPollEvents();}

        void swapBuffers() const {glfwSwapBuffers(window);}

    private:
        GLFWwindow* window;

    };

} // EE

#endif //EDENENGINE_WINDOWMANAGER_HPP
