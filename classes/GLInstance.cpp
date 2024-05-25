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
    this->windowSize = windowSize;
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
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return 0;

}

void GLInstance::renderArray(GLObject *object) {
    renderList.push_back(object);

}

// renderLoop负责每一帧画面的渲染，每轮循环会执行dynamicTransCallback函数，主要用于动态地对object做transformation
// 这里还涉及到了对不同object的贴图切换
void GLInstance::renderLoop(std::function<void(void)> *dynamicTransCallback) {
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
                    // TODO：警告：OpenGL的texture是全局的存在，而不是一个shader有16个材质槽位，而是整个OpenGL只有16个槽位。
                    object->shader.addTexture(*tex);
//                    object->textures.pop_back();
                }
            }

//          //glActiveTexture(GL_TEXTURE0);
            if(!object->mat4Uniform.empty()) {
                object->shader.setMatrix4(object->mat4Uniform, object->matrix4);
            }

//            std::cout << "addr ibo = " << (long )&object->ibo << std::endl;
            if (camera == nullptr)
                throw std::runtime_error("A Camera object is needed.");
            Camera globalCamera = *camera;
            glm::mat4 modelMat(1.0), viewMat(1.0), projectionMat(1.0);
            glm::vec3 objectPosition = object->getPosition();
            modelMat = glm::translate(modelMat, -objectPosition);
            modelMat *= object->rotate;
            object->rotate = glm::mat4(1.0f);

            viewMat = glm::lookAt(globalCamera.cameraPosition,
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
            projectionMat = glm::perspective(glm::radians(45.0f),float (windowSize.width / windowSize.height), 0.1f, 100.0f);

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

            if(dynamicTransCallback != nullptr)
                (*dynamicTransCallback)();
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

