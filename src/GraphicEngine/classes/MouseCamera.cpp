//
// Created by NoahFix on 2024/7/20.
//

#include "MouseCamera.h"

void MouseCamera::processMouse(GLFWwindow *window, double xPos, double yPos) {
    static bool first = true;
    const float sensitivity = 0.2;

    auto f_xPos = (float) xPos;
    auto f_yPos = (float) yPos;
    static float lastX = 0, lastY = 0;
    if (first) {
        yaw = 0;
        pitch = 0;
        first = false;
    } else {
        yaw += (f_xPos - lastX) * sensitivity;

        if (-(f_yPos - lastY) > 0) {
            if (pitch >= 89)
                pitch = 89;
            else
                pitch += -(f_yPos - lastY) * sensitivity;
        }

        if (-(f_yPos - lastY) < 0) {
            if (pitch <= -89)
                pitch = -89;
            else
                pitch += -(f_yPos - lastY) * sensitivity;
        }

    }

    lastX = f_xPos;
    lastY = f_yPos;
}

void MouseCamera::processInput(GLFWwindow *window) {
    static float lastTime = 0;
    float costTime = (float)glfwGetTime() - lastTime;

    glm::vec3 vecMovingForward;
    vecMovingForward.z = sin(glm::radians(yaw));
    vecMovingForward.x = cos(glm::radians(yaw));
    vecMovingForward.y = 0;

    glm::vec3& o_cameraPos = this->transformation.position;
    float cameraSpeed = 4.0f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        o_cameraPos += costTime * cameraSpeed * vecMovingForward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        o_cameraPos -= costTime * cameraSpeed * vecMovingForward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        o_cameraPos -= glm::normalize(glm::cross(vecMovingForward, glm::vec3(0, 1, 0))) * cameraSpeed * costTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        o_cameraPos += glm::normalize(glm::cross(vecMovingForward, glm::vec3(0, 1, 0))) * cameraSpeed * costTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        o_cameraPos += glm::length(vecMovingForward) * cameraSpeed * glm::vec3(0, 1, 0) * costTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        o_cameraPos -= glm::length(vecMovingForward) * cameraSpeed * glm::vec3(0, 1, 0) * costTime;

    lastTime = (float)glfwGetTime();
}

MouseCamera::MouseCamera(): CameraObject(0, 0, 0) {
    displayCursor = false;
}
