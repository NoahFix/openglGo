//
// Created by NoahFix on 2024/7/20.
//

#ifndef OPENGLGO_KEYBOARDCAMERA_H
#define OPENGLGO_KEYBOARDCAMERA_H


#include "CameraObject.h"

class KeyboardCamera: public CameraObject{
public:
    KeyboardCamera();
    void processInput(GLFWwindow *window) override;
    void processMouse(GLFWwindow *window, double xPos, double yPos) override;
};


#endif //OPENGLGO_KEYBOARDCAMERA_H
