//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_UNIFORM_H
#define OPENGLGO_UNIFORM_H
#include "GLMemoryObject.h"
#include "vec3.hpp"

class Program;
class Uniform {
    friend class Program;
private:
    int id;
    explicit Uniform(int uniformLocation);
public:
    int getID();
    void setI(int i);
    void set1f(float v1);
    void set4f(float v1, float v2, float v3, float v4);
    void set3f(float v1, float v2, float v3);
    void setVector3(const glm::vec3& vec);
};


#endif //OPENGLGO_UNIFORM_H
