//
// Created by zsy01 on 2023/9/14.
//

#include "SoftwareRenderer.hpp"
#include "Drawer/BlinnPhongDrawer.hpp"

namespace EE {
    void SoftwareRenderer::Initialize(Scene* scene, Camera* camera, WindowManager& windowManager, const std::string &vertexPath, const std::string &fragmentPath) {
        {
            this->windowManager = &windowManager;
            this->scene = scene;
            this->camera = camera;
            drawer = new BlinnPhongDrawer(windowManager.getWidth(), windowManager.getHeight(), 3, scene, camera);
            buffer = std::vector<unsigned char>(windowManager.getWidth() * windowManager.getHeight() * 3, 0);

            // Load shaders
            shaderProgram = loadShader(vertexPath, fragmentPath);

            // Set up vertex data
            float vertices[] = {
                    -1.0f, -1.0f,   0.0f, 1.0f,
                    1.0f, -1.0f,   1.0f, 1.0f,
                    1.0f,  1.0f,   1.0f, 0.0f,
                    -1.0f,  1.0f,   0.0f, 0.0f
            };

            unsigned int indices[] = {
                    0, 1, 2,
                    2, 3, 0
            };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }

    void SoftwareRenderer::Render() {
        drawer->draw(buffer);

//        for (int i = 0; i < buffer.size(); i++) {
//            if (buffer[i] != 0.f) {
//                std::cout << buffer[i] << std::endl;
//            }
//        }

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowManager->getWidth(), windowManager->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    void SoftwareRenderer::Shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    }

} // EE