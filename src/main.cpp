#include <GL/glew.h>
#include <iostream>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Render/Renderer.hpp"
#include "Utils/MeshReader.hpp"
#include "Utils//ShaderReader.hpp"
#include <assimp/Importer.hpp>
#include <GLFW/glfw3.h>

using namespace glm;
using namespace EE;

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;

int main(int argc, char** argv) {
    const std::string projectRootPath = "../";

    // Create scene
    auto* scene = new Scene();

    auto* modelReader = new MeshReader();
    modelReader->readModel(projectRootPath + "models/Stanford Bunny/", "Stanford Bunny", "dae");
//    auto *atr1 = new Actor(modelReader->getModel("Stanford Bunny"),
//                           glm::vec3 (1, 0, 0),
//                           glm::vec3(0, 0, 0),
//                           glm::vec3(7, 7, 7));
    auto *atr2 = new Actor(modelReader->getModel("Stanford Bunny"),
                           glm::vec3 (0, 0, 0),
                           glm::vec3(0, 0, 0),
                           glm::vec3(0.01, 0.01, 0.01));
//    auto *atr3 = new Actor(modelReader->getModel("Stanford Bunny"),
//                           glm::vec3 (-1, 0, 0),
//                           glm::vec3(0, 0, 0),
//                           glm::vec3(3, 3, 3));

//    scene->addActor(atr1);
    scene->addActor(atr2);
//    scene->addActor(atr3);
    auto* l1 = new PointLight(vec3(0, 0, 10), vec3(255, 255, 255), 100);

    scene->addLight(l1);

    vec3 eye(0, .9, 1.2);
    vec3 lookAt(0, 0, -1);
    vec3 up(0, 1, 0);
    float fov = 90.0f;
    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    float zNear = 0.01f;
    float zFar = 50.0f;

    auto* camera = new Camera(eye, lookAt, up, fov, aspect, zNear, zFar);
    camera->setWidth(WINDOW_WIDTH);
    camera->setHeight(WINDOW_HEIGHT);
    auto* renderer = new Renderer(scene, camera);
    renderer->setRenderMode(RenderMode::BLINN_PHONG);

    // Init glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Software Rendering to GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    std::string vertexPath = projectRootPath + "src/Shaders/SoftVSH.glsl";
    std::string fragmentPath = projectRootPath + "src/Shaders/SoftFSH.glsl";


    std::string vertexShaderStr = ShaderReader::readShader(vertexPath.c_str());
    std::string fragmentShaderStr = ShaderReader::readShader(fragmentPath.c_str());

    const char* vertexShaderSrc = vertexShaderStr.c_str();
    const char* fragmentShaderSrc = fragmentShaderStr.c_str();


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    auto* pixels = new unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT * 3];
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // render
        renderer->draw();
//        std::cout << "frame: " << renderer->getFrame(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2).r << " " << renderer->getFrame(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2).g << " " << renderer->getFrame(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2).b << std::endl;
        renderer->writeFrameBuffer2Pixel(pixels);

        // update texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        // use shader program
        glUseProgram(shaderProgram);

        // bind VAO and draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);

    glfwTerminate();
    return 0;

}
