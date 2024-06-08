//
// Created by NoahFix on 2024/6/8.
//

#ifndef OPENGLGO_GLCUBE_H
#define OPENGLGO_GLCUBE_H

#include "../GLObject.h"
class GLObject;
class Program;

class GLCube: public GLObject {
public:
    explicit GLCube(const Program &shader);
};


#endif //OPENGLGO_GLCUBE_H
