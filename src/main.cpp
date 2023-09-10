#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

using namespace glm;
using namespace EE;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void display() {
    auto* scene = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto* obj = new Object();

    auto *t1 = new Triangle();
    t1->setVertex(0, vec3(2, 0, -10));
    t1->setVertex(1, vec3(0, 2, -10));
    t1->setVertex(2, vec3(-2, 0, -10));
    t1->setColor(0, {0, 255, 0});
    t1->setColor(1, {0, 255, 0});
    t1->setColor(2, {0, 255, 0});

    auto *t2 = new Triangle();
    t2->setVertex(0, vec3(3.5, -1, 5));
    t2->setVertex(1, vec3(2.5, 1.5, 5));
    t2->setVertex(2, vec3(-1, 0.5, 1));
    t2->setColor(0, {255, 0, 0});
    t2->setColor(1, {255, 0, 0});
    t2->setColor(2, {255, 0, 0});

    obj->addTriangle(t1);
    obj->addTriangle(t2);
    scene->addObject(obj);

    vec3 eye(0, 0, -5);
    vec3 lookAt(0, 0, 1);
    vec3 up(0, 1, 0);
    float fov = 45.0f;
    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    float zNear = 0.1f;
    float zFar = 50.0f;

    auto* camera = new Camera(eye, lookAt, up, fov, aspect, zNear, zFar);
    auto* renderer = new Renderer(scene, camera);
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
