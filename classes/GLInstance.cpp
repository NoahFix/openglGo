//
// Created by NoahFix on 2024/2/14.
//

#include "GLInstance.h"
#include "../headers/glhelper.h"
#include <gtc/matrix_transform.hpp>
#include <thread>
#include "Renderer.h"

int GLInstance::begin(Rect windowSize, const std::string &title) {
    // The lack of the sentence caused crash.
    glfwInit();

    // These code is used to make glfw adapt to version 330.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize.width, windowSize.height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const GLubyte *version = glGetString(GL_VERSION);
    if (version) {
        printf("OpenGL Version: %s\n", version);
    } else {
        // 处理获取版本信息失败的情况
    }

    // Additional options
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return 0;

}

void GLInstance::renderArray(GLObject *object) {
    renderList.push_back(object);

}

void GLInstance::renderLoop() {
    while (!glfwWindowShouldClose(GLInstance::window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 注意：这里必须写 GLObject &object:renderList 不能写成： GLObject object:renderList 否则图像只会闪现而过！！！
        // TODO: or (GLObject &object:renderList) 竟然能发生复制object？？？
        for(GLObject *object:renderList) {
            // Draw main objects
            Renderer::init(&object->ibo, &object->shader, &object->vertexArray, &object->vertexBuffer);

            // Texture 对象存储着一张贴图，Texture 由每个GLObject掌控，这是因为Texture 对象不能一生成就绑定到shader，必须在shader绑定后（也就上一行Renderer::init后）才能绑定texture对象
            if(!object->textures.empty()) {
                for(const Texture *tex:object->textures) {
                    object->shader.addTexture(*tex);
                    object->textures.pop_back();
                }
            }
            if(!object->mat4Uniform.empty()) {
                object->shader.setMatrix4(object->mat4Uniform, object->matrix4);
            }

//            std::cout << "addr ibo = " << (long )&object->ibo << std::endl;
            glm::mat4 modelMat(1.0), viewMat(1.0), projectionMat(1.0);
            glm::vec3 objectPosition = object->getPosition();
            modelMat = glm::translate(modelMat, -objectPosition);
            modelMat *= object->rotate;


            object->shader.setMatrix4("modelMat", modelMat);
            object->shader.setMatrix4("viewMat", viewMat);
            object->shader.setMatrix4("projectionMat", projectionMat);


            if (object->ibo.isNullIBO()) {
                int v = object->vertexBuffer.size / object->vertexArray.getEachVertexSize();
//                std::cout << "v(vertexes to be drawn) is: " << v << std::endl;
                Renderer::renderArrays(v);
            } else {
                int v = object->ibo.getIndicesCount();
//                std::cout << "v(IBO to be drawn) is: " << v << std::endl;
                glDrawElements(GL_TRIANGLES, v, GL_UNSIGNED_INT, 0);
            }

        }

        /* Swap front and back buffers */
        glfwSwapBuffers(GLInstance::window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

GLFWwindow *GLInstance::getWindowPtr() {
    return GLInstance::window;
}

void GLInstance::setCamera(const Camera &camera) {
    this->camera = &camera;

}

