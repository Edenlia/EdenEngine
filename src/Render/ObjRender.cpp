
#include <string>
#include "ObjRender.hpp"
#include <glm/gtc/type_ptr.hpp>


namespace EE {
    ObjRender::ObjRender(Object *object, RenderInfo *renderInfo) {
        this->object = object;
        this->renderInfo = renderInfo;
        shader = new Shader(renderInfo->vertexShader, renderInfo->fragmentShader);

        glEnable(GL_DEPTH_TEST);

        glUseProgram(shader->shaderProgram);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &positionVBO);
        glGenBuffers(1, &normalVBO);
        glGenBuffers(1, &texcoordVBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        std::vector<float> vertices = object->getMesh()->getVertices();
        std::vector<float> normals = object->getMesh()->getNormals();
        std::vector<float> uvs = object->getMesh()->getUVs();
        std::vector<unsigned int> indices = object->getMesh()->getIndices();

        glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        textureID1 = loadTexture(object->getMesh()->getMaterial()->getAlbedoMap(), "uAlbedoTexture", 0);
        textureID2 = loadTexture(object->getMesh()->getMaterial()->getNormalMap(), "uNormalTexture", 1);


//        GLenum err;
//        while ((err = glGetError()) != GL_NO_ERROR) {
//            std::cerr << "OpenGL error: " << err << std::endl;
//        }
    }

    // TODO: fix bug
    void ObjRender::bindGeometryInfo() {
        glBindVertexArray(VAO);

        std::vector<float> vertices = object->getMesh()->getVertices();
        std::vector<float> normals = object->getMesh()->getNormals();
        std::vector<float> uvs = object->getMesh()->getUVs();
        std::vector<unsigned int> indices = object->getMesh()->getIndices();

        glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void ObjRender::bindMaterialInfo() {
        glUseProgram(shader->shaderProgram);

        for (auto& glslData : renderInfo->glslUniformData) {
            bindUniformData(glslData);
        }
    }

    void ObjRender::bindCameraInfo(Camera *camera) {
        glUseProgram(shader->shaderProgram);

        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::vec3 cameraPos = camera->getPosition();

        GLSLData v = {"uView", MAT4, view};
        GLSLData p = {"uProjection", MAT4, projection};
        GLSLData pos = {"uCameraPos", VEC3, cameraPos};

        bindUniformData(v);
        bindUniformData(p);
        bindUniformData(pos);

//        GLint viewLocation = glGetUniformLocation(shader->shaderProgram, "uView");
//        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//
//        GLint projectionLocation = glGetUniformLocation(shader->shaderProgram, "uProjection");
//        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//
//        GLint cameraPosLocation = glGetUniformLocation(shader->shaderProgram, "uCameraPos");
//        glUniform3f(cameraPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
    }

    GLuint ObjRender::loadTexture(const std::shared_ptr<Texture> &texture, const std::string &name, int index) {
        GLuint textureID;
        glGenTextures(1, &textureID);

        int width = texture->width;
        int height = texture->height;
        unsigned char* data = texture->raw_data;

        GLenum format;
        if (texture->channel == 1)
            format = GL_RED;
        else if (texture->channel == 3)
            format = GL_RGB;
        else if (texture->channel == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int textureLocation = glGetUniformLocation(shader->shaderProgram, name.c_str());

        glUniform1i(textureLocation, index);

//        if (index == 0) {
//            glActiveTexture(GL_TEXTURE0);
//        }
//        else {
//            glActiveTexture(GL_TEXTURE1);
//        }

        glBindTexture(GL_TEXTURE_2D, textureID);

        return textureID;
    }

    void ObjRender::render(Camera *camera) {
        glUseProgram(shader->shaderProgram);
        glBindVertexArray(VAO);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        bindGeometryInfo();
        bindMaterialInfo();
        bindCameraInfo(camera);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureID2);


        glDrawElements(GL_TRIANGLES, object->getMesh()->getIndicesNum(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

    }

    void ObjRender::bindUniformData(GLSLData &glslData) {
        GLint uniformLocation = glGetUniformLocation(shader->shaderProgram, glslData.name.c_str());

        if (uniformLocation == -1) {
//            std::cout << "Warning: uniform " << glslData.name << " not found" << std::endl;
            return;
        }

        switch (glslData.type) {
            case FLOAT: {
                glUniform1f(uniformLocation, std::get<float>(glslData.value));
                break;
            }
            case VEC2: {
                glUniform2f(uniformLocation, std::get<glm::vec2>(glslData.value).x, std::get<glm::vec2>(glslData.value).y);
                break;
            }
            case VEC3: {
                glUniform3f(uniformLocation, std::get<glm::vec3>(glslData.value).x, std::get<glm::vec3>(glslData.value).y, std::get<glm::vec3>(glslData.value).z);
                break;
            }
            case VEC4: {
                glUniform4f(uniformLocation, std::get<glm::vec4>(glslData.value).x, std::get<glm::vec4>(glslData.value).y, std::get<glm::vec4>(glslData.value).z, std::get<glm::vec4>(glslData.value).w);
                break;
            }
            case MAT4: {
                glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(glslData.value)));
                break;
            }
        }

    }
} // EE