#include <iostream>
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Utils/MeshReader.hpp"
#include "Display/WindowManager.hpp"
#include "Render/SRenderer.hpp"
#include "RenderInfo/PhongRenderInfo.hpp"
#include "Render/ObjRender.hpp"
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
//    auto *atr1 = new Actor(modelReader->getMesh("Stanford Bunny"),
//                           glm::vec3 (1, 0, 0),
//                           glm::vec3(0, 0, 0),
//                           glm::vec3(7, 7, 7));
    auto *atr2 = new Actor(modelReader->getModel("Stanford Bunny"),
                           glm::vec3(0, 0, 0),
                           glm::vec3(0, 0, 0),
                           glm::vec3(0.01, 0.01, 0.01));
//    auto *atr3 = new Actor(modelReader->getMesh("Stanford Bunny"),
//                           glm::vec3 (-1, 0, 0),
//                           glm::vec3(0, 0, 0),
//                           glm::vec3(3, 3, 3));
//    scene->addActor(atr1);
    scene->addActor(atr2);
//    scene->addActor(atr3);
    auto* l1 = new PointLight( vec3(255, 255, 255),
                               100,
                               vec3(0, 0, 10),
                               vec3(0, 0, 0),
                               vec3(1, 1, 1));

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

    WindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Renderer", camera);



    std::string vertexPath = projectRootPath + "src/Shader/Phong/PhongVSH.glsl";
    std::string fragmentPath = projectRootPath + "src/Shader/Phong/PhongFSH.glsl";

    Object* obj = scene->getActors()[0];
    Light* light = scene->getLights()[0];

    RenderInfo *renderInfo = new PhongRenderInfo(light, obj->getModelMatrix(), vertexPath, fragmentPath);

    auto* renderer = new ObjRender(obj, renderInfo);
    while (!windowManager.shouldClose()) {

        EE::WindowManager::pollEvents();
        camera->setDeltaTime(windowManager.getDeltaTime());

        renderer->render(camera);

        windowManager.swapBuffers();
    }
    renderer->shutdown();

//    std::string vertexPath = projectRootPath + "src/Shader/Software/SoftwareVSH.glsl";
//    std::string fragmentPath = projectRootPath + "src/Shader/Software/SoftwareFSH.glsl";
//
//    auto* renderer = new SRenderer();
//    renderer->Initialize(scene, camera, windowManager, vertexPath, fragmentPath);
//
//    while (!windowManager.shouldClose()) {
//        renderer->Render();
//        windowManager.swapBuffers();
//        EE::WindowManager::pollEvents();
//    }
//
//    renderer->Shutdown();
}
