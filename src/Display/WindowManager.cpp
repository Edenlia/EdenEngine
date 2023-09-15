//
// Created by zsy01 on 2023/9/14.
//

#include "WindowManager.hpp"

namespace EE {
    WindowManager::WindowManager(int width, int height, const char *title) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        this->width = width;
        this->height = height;
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);
        glewInit();
    }
} // EE