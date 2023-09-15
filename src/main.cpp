#include <iostream>
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Utils/MeshReader.hpp"
#include "Display/WindowManager.hpp"
#include "Render/SoftwareRenderer.hpp"
#include <assimp/Importer.hpp>

using namespace glm;
using namespace EE;

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;

const std::string projectRootPath = "../";

void buildScene(Scene* scene, Camera* camera) {
    camera->setWidth(WINDOW_WIDTH);
    camera->setHeight(WINDOW_HEIGHT);

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
}

int main(int argc, char** argv) {
//    auto* windowManager = new WindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Renderer");
//    auto* window = windowManager->getWindow();

    // Create scene and camera
    auto* scene = new Scene();

    vec3 eye(0, .9, 1.2);
    vec3 lookAt(0, 0, -1);
    vec3 up(0, 1, 0);
    float fov = 90.0f;
    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    float zNear = 0.01f;
    float zFar = 50.0f;

    auto* camera = new Camera(eye, lookAt, up, fov, aspect, zNear, zFar);

    buildScene(scene, camera);

    WindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Renderer");

    std::string vertexPath = projectRootPath + "src/Shader/SoftVSH.glsl";
    std::string fragmentPath = projectRootPath + "src/Shader/SoftFSH.glsl";

    std::unique_ptr<SoftwareRenderer> renderer;
    renderer = std::make_unique<SoftwareRenderer>();
    renderer->Initialize(scene, camera, windowManager, vertexPath, fragmentPath);

    while (!windowManager.shouldClose()) {
        renderer->Render();
        windowManager.swapBuffers();
        EE::WindowManager::pollEvents();
    }
    renderer->Shutdown();
}
