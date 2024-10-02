//
// Created by NoahFix on 2024/7/20.
//

#ifndef OPENGLGO_MOUSECAMERA_H
#define OPENGLGO_MOUSECAMERA_H


#include "CameraObject.h"

class MouseCamera: public CameraObject{
public:
    MouseCamera();
    void processMouse(GLFWwindow *window, double xPos, double yPos) override;
    void processInput(GLFWwindow *window) override;
};


#endif //OPENGLGO_MOUSECAMERA_H
