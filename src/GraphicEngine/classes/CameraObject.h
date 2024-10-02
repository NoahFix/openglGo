//
// Created by NoahFix on 2024/2/13.
//

#ifndef OPENGLGO_CAMERAOBJECT_H
#define OPENGLGO_CAMERAOBJECT_H

#include "glm.hpp"
#include "GERenderableObject.h"

class CameraObject: public GEObject {
public:
    CameraObject(float x, float y, float z);

    virtual ~CameraObject() = default;

    void setCameraPosition(float x, float y, float z);
    virtual void processInput(GLFWwindow *window) = 0;
    virtual void processMouse(GLFWwindow *window, double xPos, double yPos) = 0;

    bool displayCursor = false;
    float pitch = 0;
    float yaw = 0;
};


#endif //OPENGLGO_CAMERAOBJECT_H
