//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_SHADER_H
#define OPENGLGO_SHADER_H

#include <string>
#include "GLMemoryObject.h"

class Program;
class Shader: public GLMemoryObject{
    friend class Program;
public:
    explicit Shader(std::string &src, unsigned int type);
    ~Shader();
};


#endif //OPENGLGO_SHADER_H
