//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_UNIFORM_H
#define OPENGLGO_UNIFORM_H
#include "GLMemoryObject.h"

class Program;
class Uniform {
    friend class Program;
private:
    int id;
    explicit Uniform(int uniformLocation);
public:
    int getID();
    void setI(int i);
    void set4f(float v1, float v2, float v3, float v4);
};


#endif //OPENGLGO_UNIFORM_H
