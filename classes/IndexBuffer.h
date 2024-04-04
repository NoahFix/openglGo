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
    bool isNullIBO();
    int getIndicesCount();
    ~IndexBuffer();

    void bind() override;
    void unbind() override;
private:
    int size = 0;
};


#endif //OPENGLGO_INDEXBUFFER_H
