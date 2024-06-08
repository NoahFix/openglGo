//
// Created by NoahFix on 2024/2/13.
//

#ifndef OPENGLGO_CAMERA_H
#define OPENGLGO_CAMERA_H

#include "glm.hpp"

class Camera {
public:
    Camera(float x, float y, float z);
    void setCameraPosition(float x, float y, float z);

    glm::vec3 forward;
    glm::vec3 cameraPosition;

};


#endif //OPENGLGO_CAMERA_H
