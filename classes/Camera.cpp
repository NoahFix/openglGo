//
// Created by NoahFix on 2024/2/13.
//

#include "Camera.h"

Camera::Camera(float x, float y, float z) {
    setCameraPosition(x, y, z);

}

void Camera::setCameraPosition(float x, float y, float z) {
    this->cameraPosition.x = x;
    this->cameraPosition.y = y;
    this->cameraPosition.z = z;
}
