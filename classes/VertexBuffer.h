//
// Created by NoahFix on 2024/2/1.
//

#ifndef OPENGLGO_VERTEXBUFFER_H
#define OPENGLGO_VERTEXBUFFER_H
#include "glad/glad.h"
#include <GLFW/glfw3.h>
//#include <string>
//#include <iostream>
#include <cstdio>
#include "GLMemoryObject.h"
#include "BindableObject.h"

class GLInstance;

class VertexBuffer final : public GLMemoryObject, BindableObject {
    friend class GLInstance;
public:
    VertexBuffer(unsigned long size, char *data);
    ~VertexBuffer();
    void bind() override;
    void unbind() override;
private:
    unsigned long size;
};


#endif //OPENGLGO_VERTEXBUFFER_H
