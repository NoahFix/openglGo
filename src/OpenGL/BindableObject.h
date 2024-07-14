//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_BINDABLEOBJECT_H
#define OPENGLGO_BINDABLEOBJECT_H
#include "GLMemoryObject.h"

class BindableObject {
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;

};


#endif //OPENGLGO_BINDABLEOBJECT_H
