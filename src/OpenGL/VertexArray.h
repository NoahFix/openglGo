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

    void setVertexBufferObject(VertexBuffer &vbo, const VertexMemoryLayout &memLayout);
    unsigned long getEachVertexSize() const;
private:
    unsigned long offset = 0;
};


#endif //OPENGLGO_VERTEXARRAY_H
