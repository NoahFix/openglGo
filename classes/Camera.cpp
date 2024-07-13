//
// Created by NoahFix on 2024/2/13.
//

#include "Camera.h"
#include <iostream>

Camera::Camera(float x, float y, float z) {
    setCameraPosition(x, y, z);

}

void Camera::setCameraPosition(float x, float y, float z) {
    this->cameraPosition.x = x;
    this->cameraPosition.y = y;
    this->cameraPosition.z = z;
}

void Camera::lookAt(glm::vec3 pointPosition) {
    yaw = atan((pointPosition.z - cameraPosition.z) / (pointPosition.y - cameraPosition.z));
    pitch = atan((pointPosition.y - cameraPosition.y) / (pointPosition.x - cameraPosition.x));

    std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
}

