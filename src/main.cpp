#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "util/ModelReader.hpp"
#include <assimp/Importer.hpp>
#include <fstream>

using namespace glm;
using namespace EE;

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;

void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void display() {
    auto* scene = new Scene();

    auto* modelReader = new ModelReader();
    modelReader->readModel("../models/Stanford Bunny/", "Stanford Bunny", "dae");
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
    float zNear = 0.1f;
    float zFar = 50.0f;

    auto* camera = new Camera(eye, lookAt, up, fov, aspect, zNear, zFar);
    camera->setWidth(WINDOW_WIDTH);
    camera->setHeight(WINDOW_HEIGHT);
    auto* renderer = new Renderer(scene, camera);
    renderer->setRenderMode(RenderMode::BLINN_PHONG);
    renderer->draw();

    glClear(GL_COLOR_BUFFER_BIT);

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            vec3 color = renderer->getFrame(x, y);
//            vec3 color = vec3(1, 1, 1);
            setPixel(x, y, color.r, color.g, color.b);
        }
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Rasterizer");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
