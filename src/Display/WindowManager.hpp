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
    public:
        WindowManager(int width, int height, const char* title) ;

        ~WindowManager() {
            glfwTerminate();
        }

        [[nodiscard]] GLFWwindow* getWindow() const {return window;}

        [[nodiscard]] bool shouldClose() const {return glfwWindowShouldClose(window);}

        static void pollEvents() {glfwPollEvents();}

        void swapBuffers() const {glfwSwapBuffers(window);}

        [[nodiscard]] int getWidth() const {return width;}
        [[nodiscard]] int getHeight() const {return height;}

    private:
        GLFWwindow* window;
        int width;
        int height;
    };

} // EE

#endif //EDENENGINE_WINDOWMANAGER_HPP
