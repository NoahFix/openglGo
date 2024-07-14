//
// Created by NoahFix on 2024/6/8.
//

#ifndef OPENGLGO_GLCUBE_H
#define OPENGLGO_GLCUBE_H

#include "classes/GERenderableObject.h"
class GERenderableObject;
class Program;

class GLCube: public GERenderableObject {
public:
    explicit GLCube(const Program &shader);
};


#endif //OPENGLGO_GLCUBE_H
