//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_VERTEXARRAY_H
#define OPENGLGO_VERTEXARRAY_H
#include "GLMemoryObject.h"
#include "BindableObject.h"
#include "VertexBuffer.h"
#include "VertexMemoryLayout.h"


class VertexArray: public GLMemoryObject, BindableObject {
public:
    VertexArray();
    ~VertexArray();
    void bind() override;
    void unbind() override;

    void addVertexBufferObject(VertexBuffer &vbo, VertexMemoryLayout &memLayout);
};


#endif //OPENGLGO_VERTEXARRAY_H
