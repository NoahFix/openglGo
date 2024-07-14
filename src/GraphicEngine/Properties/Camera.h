//
// Created by NoahFix on 2024/7/14.
//

#include "vec3.hpp"

#ifndef OPENGLGO_CAMERA_H
#define OPENGLGO_CAMERA_H

class Camera {
public:
    float pitch = 0;
    float yaw = 0;
    glm::vec3 sightVector;
};

#endif //OPENGLGO_CAMERA_H
