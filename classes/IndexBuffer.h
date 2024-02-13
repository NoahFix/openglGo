//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_INDEXBUFFER_H
#define OPENGLGO_INDEXBUFFER_H
#include "BindableObject.h"
#include "GLMemoryObject.h"

class IndexBuffer final : public GLMemoryObject, BindableObject{
public:
    IndexBuffer(int size, char *data);
    ~IndexBuffer();

    void bind() override;
    void unbind() override;
};


#endif //OPENGLGO_INDEXBUFFER_H
