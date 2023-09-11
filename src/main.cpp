#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

    Assimp::Importer importer;

    const aiScene *as = importer.ReadFile("../models/bunny/bunny.obj",
                                          aiProcess_Triangulate |
                                          aiProcess_JoinIdenticalVertices |
                                          aiProcess_GenSmoothNormals
    );

    if (!as || as->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !as->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        exit(-1);
    }

    for (int i = 0; i < as->mNumMeshes; i++) {
        aiMesh *mesh = as->mMeshes[i];
        assert(mesh->HasNormals());
        auto* obj = new Object();
        for (int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            auto *triangle = new Triangle();
            assert(face.mNumIndices == 3);
            for (int k = 0; k < face.mNumIndices; k++) {
                int index = face.mIndices[k];
                aiVector3D vertex = mesh->mVertices[index];
                aiColor4D color;
                if (!mesh->HasVertexColors(0)) {
                    color = aiColor4D(1.0f, 0.0f, 0.0f, 1.0f);
                } else {
                    color = mesh->mColors[0][index];
                }
                aiVector3D normal = mesh->mNormals[index];
//                std::cout << "normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;

                triangle->setVertex(k, vec3(vertex.x, vertex.y, vertex.z));
                triangle->setColor(k, vec3(color.r, color.g, color.b));
                triangle->setNormal(k, vec3(normal.x, normal.y, normal.z));
            }
            obj->addTriangle(triangle);
        }
        scene->addObject(obj);
    }

//    auto *t1 = new Triangle();
//    t1->setVertex(0, vec3(2, 0, 3));
//    t1->setVertex(1, vec3(0, 2, 3));
//    t1->setVertex(2, vec3(-2, 0, 3));
//    t1->setColor(0, {1, 0, 0});
//    t1->setColor(1, {0, 1, 0});
//    t1->setColor(2, {0, 0, 1});
//
//    auto *t2 = new Triangle();
//    t2->setVertex(0, vec3(3.5, -1, 5));
//    t2->setVertex(1, vec3(2.5, 1.5, 5));
//    t2->setVertex(2, vec3(-1, 0.5, 1));
//    t2->setColor(0, {1, 0, 0});
//    t2->setColor(1, {1, 0, 0});
//    t2->setColor(2, {1, 0, 0});

//    obj->addTriangle(t1);
//    obj->addTriangle(t2);

    vec3 eye(0, .3, .5);
    vec3 lookAt(0, 0, -1);
    vec3 up(0, 1, 0);
    float fov = 45.0f;
    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    float zNear = 0.1f;
    float zFar = 50.0f;

    auto* camera = new Camera(eye, lookAt, up, fov, aspect, zNear, zFar);
    auto* renderer = new Renderer(scene, camera);
    renderer->setRenderMode(RenderMode::NORMAL);
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
