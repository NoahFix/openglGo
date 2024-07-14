//
// Created by NoahFix on 2024/2/13.
//

#include "CameraObject.h"
#include <iostream>

CameraObject::CameraObject(float x, float y, float z) {
    setCameraPosition(x, y, z);

}

void CameraObject::setCameraPosition(float x, float y, float z) {
    this->transformation.position.x = x;
    this->transformation.position.y = y;
    this->transformation.position.z = z;
}

void CameraObject::lookAt(glm::vec3 pointPosition) {
    yaw = atan((pointPosition.z - transformation.position.z) / (pointPosition.y - transformation.position.z));
    pitch = atan((pointPosition.y - transformation.position.y) / (pointPosition.x - transformation.position.x));

    std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
}

