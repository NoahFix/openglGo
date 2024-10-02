//
// Created by NoahFix on 2024/7/20.
//

#include "KeyboardCamera.h"

void KeyboardCamera::processInput(GLFWwindow *window) {
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


    float sightMovingSpeed = 90;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        yaw -= sightMovingSpeed * costTime;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        yaw += sightMovingSpeed * costTime;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (pitch >= 89.0f)
            pitch = 89.9f;
        else
            pitch += sightMovingSpeed * costTime;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (pitch <= -89.0f)
            pitch = -89.9f;
        else
            pitch -= sightMovingSpeed * costTime;
    }
    lastTime = (float)glfwGetTime();
}

void KeyboardCamera::processMouse(GLFWwindow *window, double xPos, double yPos) {

}

KeyboardCamera::KeyboardCamera():CameraObject(0, 0, 0) {
    displayCursor = true;
}
