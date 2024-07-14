//
// Created by NoahFix on 2024/2/13.
//

#ifndef OPENGLGO_CAMERAOBJECT_H
#define OPENGLGO_CAMERAOBJECT_H

#include "glm.hpp"
#include "GERenderableObject.h"
#include "Properties/Camera.h"

class CameraObject: public GEObject, public Camera {
public:
    CameraObject(float x, float y, float z);
    void setCameraPosition(float x, float y, float z);
    void lookAt(glm::vec3 pointPosition);

};


#endif //OPENGLGO_CAMERAOBJECT_H
