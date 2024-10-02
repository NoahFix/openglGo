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
    GLCube(const Program &shader, const VertexMemoryLayout &layout);

    GLCube(const Program &shader, bool withBuiltInNormalsData);
};


#endif //OPENGLGO_GLCUBE_H
