#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "classes/VertexArray.h"
#include "classes/VertexBuffer.h"
#include "classes/Shader.h"
#include "classes/Program.h"
#include "headers/glhelper.h"
#include "classes/IndexBuffer.h"
#include "classes/VertexMemoryLayout.h"
#include "classes/Renderer.h"
#include "libraries/stb_image.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "classes/GLInstance.h"
#include "classes/GLObject.h"
//float yaw;
//float pitch;
//static float lastX, lastY;
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    float xOffset = (float)(xpos - lastX);
//    float yOffset = (float)(lastY - ypos); // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.3f;
//    xOffset *= sensitivity;
//    yOffset *= sensitivity;
//
////    std::cout << xOffset << std::endl;
//
//    std::cout << "Pitch: " << pitch << ", Yaw: " << yaw  << ", sin(pitch) = " << sin(glm::radians(pitch)) << std::endl;
//    yaw   += xOffset;
//    pitch += yOffset;
//
//    // 在这里我们使用了 89.0f 来限制pitch，表示我们已经将其看作一个角度制的角了！所以必须用 glm::radian()
//    if(pitch > 89.0f)
//        pitch =  89.0f;
//    if(pitch < -89.0f)
//        pitch = -89.0f;
//}
//
//void processInput(GLFWwindow *window, glm::vec3 &o_cameraPos, const glm::vec3 &i_vectorForward) {
//    static float lastTime = 0;
//    float costTime = (float)glfwGetTime() - lastTime;
//    glm::vec3 localVecForward;
//    localVecForward.x = i_vectorForward.x;
//    localVecForward.z = i_vectorForward.z;
//    localVecForward.y = 0;
//
//    float cameraSpeed = 6.0f; // adjust accordingly
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        o_cameraPos += costTime * cameraSpeed * localVecForward;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        o_cameraPos -= costTime * cameraSpeed * localVecForward;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        o_cameraPos -= glm::normalize(glm::cross(localVecForward, glm::vec3(0, 1, 0))) * cameraSpeed * costTime;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        o_cameraPos += glm::normalize(glm::cross(localVecForward, glm::vec3(0, 1, 0))) * cameraSpeed * costTime;
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//        o_cameraPos += glm::length(localVecForward) * cameraSpeed * glm::vec3(0, 1, 0) * costTime;
//    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//        o_cameraPos -= glm::length(localVecForward) * cameraSpeed * glm::vec3(0, 1, 0) * costTime;
//
//    lastTime = (float)glfwGetTime();
//}
//
//
//
//
//
//// Here's an interesting phenomenon: Shader.h and Program.h included each other, which caused complex including problems.
//// If we both include Shader.h and Program.h.It will lead to an error.
//// Well, it's a looped including.
//
//// 当多个源文件要引用同一个头文件时，仅仅使用ifndef是不行的，必须把头文件中所有的函数都加上static（这些函数的声明和实现都在同一个头文件中）
//
//// Slot is an important concept in opengl!!!
//
//// Data
//float vertices[] = {    // Position(x, y)    Colour R, G, B)    Texture(x, y)
//        -0.5, -0.5,     0.0, 1.0, 0.0,      1.0, 1.0,
//        -0.5, 0.5,      1.0, 0.0, 0.0,    1.0, 0.0,
//        0.5, 0.5,     0.0, 0.0, 1.0,    0.0, 0.0,
//        0.5, -0.5,    1.0, 1.0, 0.0 ,  0.0, 1.0
//};
//
//float verticesCube[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
//unsigned int vertexIndex[] = {
//        0, 1, 2,
//        3, 4, 5,
//        6, 7, 8,
//        9, 10, 11,
//        12, 13, 14,
//        15,16,17,
//        18,19,20,
//        21,22,23,
//        24,25,26,27,28,29,30,31,32,33,34,35
//};
//
//int main()
//{
//
//    GLFWwindow *glfwWindow;
//    if (GLInit(&glfwWindow) == -1) return -1;
//    glfwSetCursorPosCallback(glfwWindow, mouse_callback);
//    int tmpX, tmpY;
//    glfwGetWindowSize(glfwWindow, &tmpX, &tmpY);
//    lastX = tmpX;
//    lastY = tmpY;
//    lastX /= 2;
//    lastY /= 2;
//
//    glm::vec3 cubePositions[] = {
//            glm::vec3( 0.0f,  0.0f,  0.0f),
//            glm::vec3( 2.0f,  5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3( 2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f,  3.0f, -7.5f),
//            glm::vec3( 1.3f, -2.0f, -2.5f),
//            glm::vec3( 1.5f,  2.0f, -2.5f),
//            glm::vec3( 1.5f,  0.2f, -1.5f),
//            glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    // Generate a buffer to store data
//    VertexArray vaoObjects, vaoLight;
//    VertexBuffer vbo(sizeof(verticesCube), (char *)verticesCube);
//
//    VertexMemoryLayout layoutObjects;
//    layoutObjects.pushFloat(3);    // Position(x, y, z)
//    layoutObjects.pushFloat(2);    // Texture(x, y)
//
//    VertexMemoryLayout layoutLights;
//    layoutLights.pushFloat(3); // Position
//
//    vaoObjects.addVertexBufferObject(vbo, layoutObjects);
//    vaoLight.addVertexBufferObject(vbo, layoutLights);
//
//    // Create shaders
//    std::string vs;
//    readShader("assets/shaders/BasicVertex.vs.vert", vs);
//    std::string fs;
//    readShader("assets/shaders/BasicFragment.fs.frag", fs);
//    Shader fragmentShader(fs, GL_FRAGMENT_SHADER), vertexShader(vs, GL_VERTEX_SHADER);
//    Program program(vertexShader, fragmentShader);
//
//    IndexBuffer ibo(sizeof(vertexIndex), reinterpret_cast<char *>(vertexIndex));
//
//    Texture texture1("assets/pictures/container.jpg", "texture1", false),
//            texture2("assets/pictures/awesomeface.png", "texture2",true);
//
////    glm::mat4 viewMat(1.0), projectionMat(1.0);
////    // OpenGL 的坐标系是右手坐标系，所以x轴的表示方法是 (1.0, 0.0, 0.0)
////    // Model mat的变化使得物体旋转，但仍在世界中心。
////    // view mat 定义了摄像机的位置
////    viewMat = glm::translate(viewMat, glm::vec3(0.0, -0.0, -3.0));
////    // projectionMat 定义了摄像机的拍摄角度
////    projectionMat = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//    int modelMatUni = glGetUniformLocation(program.getID(), "modelMat");
//    int viewMatUni = glGetUniformLocation(program.getID(), "viewMat");
//    int projectionMatUni = glGetUniformLocation(program.getID(), "projectionMat");
//
//    glm::vec3 cameraPos(0, 0, -3);
//    glm::vec3 vectorForward(0, 0, -1);
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(glfwWindow))
//    {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Draw main objects
//        Renderer::init(&ibo, &program, &vaoObjects, &vbo);
//        // 必须在设定uniform前绑定shader程序
//        program.addTexture(texture1);
//        program.addTexture(texture2);
//
//        vectorForward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//        vectorForward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//        vectorForward.y = sin(glm::radians(pitch));
//        vectorForward = glm::normalize(vectorForward);
//        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        glm::mat4 projection    = glm::mat4(1.0f);
////        float fov = 20 + (float)abs(90*sin(2 * 3.1415926535 / 6 * glfwGetTime()));
////        std::cout << "FOV: " << fov << std::endl;
//        projection = glm::perspective(glm::radians(50.0f), (float)800 / (float)600, 0.1f, 100.0f);
////        projection = glm::rotate(projection, glm::radians(0.0f), glm::vec3(0, 1, 0));
//
//        glm::vec3 vecMovingForward;
//        vecMovingForward.z = sin(glm::radians(yaw));
//        vecMovingForward.x = cos(glm::radians(yaw));
//        vecMovingForward.y = 0;
//        processInput(glfwWindow, cameraPos, vecMovingForward);
//        glm::mat4 lookAt = glm::lookAt(cameraPos, cameraPos + vectorForward, glm::vec3(0, 1, 0));
//        view       = lookAt;
//
////        {
////            glm::mat4 model(1.0);
////            model = glm::translate(model, glm::vec3(-0.9, 0.2, -2));
////
////            glUniformMatrix4fv(viewMatUni, 1, GL_FALSE, glm::value_ptr(view));
////            glUniformMatrix4fv(projectionMatUni, 1, GL_FALSE, glm::value_ptr(projection));
////            glUniformMatrix4fv(modelMatUni, 1, GL_FALSE, glm::value_ptr(model));
////            glDrawArrays(GL_TRIANGLES, 0, 36);
////
////        }
////
////        {
////            glm::mat4 model(1.0);
////            model = glm::translate(model, glm::vec3(0, 0, -7));
////            glUniformMatrix4fv(modelMatUni, 1, GL_FALSE, glm::value_ptr(model));
////            glDrawArrays(GL_TRIANGLES, 0, 36);
////
////        }
//        glUniformMatrix4fv(viewMatUni, 1, GL_FALSE, glm::value_ptr(view));
//        glUniformMatrix4fv(projectionMatUni, 1, GL_FALSE, glm::value_ptr(projection));
//        static float ang;
//        for (int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            if(i >= 5) {
//                ang += 0.1;
//                model = glm::rotate(model, glm::radians(i * 20.0f + (float)ang),glm::vec3(0.8, 0.3, 0));
//            }
//            glUniformMatrix4fv(modelMatUni, 1, GL_FALSE, glm::value_ptr(model));
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        }
//
//        // Draw lights
//        Renderer::init(nullptr, &program, &vaoLight, &vbo);
//        Renderer::renderArrays(36);
//
////        u_color.set4f(0, abs(sin((2 * 3.1415926535 / blinkingT / 2) * glfwGetTime())), 0, 0);
//        // glDrawElements() can automatically copy texture to uniform.
//        /* Render here */
////        Renderer::render(sizeof(vertexIndex) / sizeof (unsigned int));
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(glfwWindow);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}
//// 共有四个顶点，画一个矩形
//float vertices[] = {    // Position(x, y)     Texture(x, y)
//        -0.5, -0.5, 1.0, 1.0,
//        -0.5, 0.5,  1.0, 0.0,
//        0.5, 0.5,   0.0, 0.0,
//        0.5, -0.5,0.0, 1.0
//};

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int main() {
    GLInstance &glInstance = GLInstance::getInstance();
    glInstance.begin({800, 600}, "Hello glPackage");
    VertexMemoryLayout layout;
    layout.pushFloat(3);    // Space position
    layout.pushFloat(2);    // Texture position
    Program shaderSmileBox = Program("assets/shaders/vertTest.glsl", "assets/shaders/fragTest.glsl");
    Program shaderChest = Program("assets/shaders/vertTest.glsl", "assets/shaders/fragTest.glsl");


    Texture texture1("assets/pictures/awesomeface.png", "textureUniform"),
            texture2("assets/pictures/container.jpg", "textureUniform", false);

    GLObject secondObj((char*)vertices, sizeof(vertices), shaderChest, layout);
    secondObj.addTexture(texture2);
    secondObj.setPosition(-2, 0, 0);

    GLObject firstObj((char*)vertices, sizeof(vertices), shaderSmileBox, layout);
    firstObj.addTexture(texture1);
    firstObj.setPosition(0, 0, 0);



    Camera camera(0, 3, 4);

    glInstance.setCamera(camera);
    glInstance.renderArray(&secondObj);
    glInstance.renderArray(&firstObj);
    firstObj.addRotate(20, glm::vec3(0, 1, 0));


    std::function<void(void)> cb = [&firstObj]() -> void{
        firstObj.addRotate(abs(90 * sin(2 * 3.1415926535 / 2 * glfwGetTime())), glm::vec3(0, 1, 0));
    };

    glInstance.renderLoop(&cb);
    return 0;
}