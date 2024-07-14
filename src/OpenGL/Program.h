//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_PROGRAM_H
#define OPENGLGO_PROGRAM_H

#include "Shader.h"
#include "GLMemoryObject.h"
#include "BindableObject.h"
#include "Uniform.h"
#include "Texture.h"
#include "glm.hpp"


class Program: public GLMemoryObject, BindableObject {
public:
    Program(const Shader& vs, const Shader& fs);
    Program(const std::string& vsFilePath, const std::string& fsFilePath);
    ~Program();
    unsigned int getID();
    void bind() override;
    void unbind() override;
    void setI(const std::string &name, int v);
    void set4f(const std::string &name, int v1, int v2, int v3, int v4);
    void setMatrix4(const std::string &name, glm::mat4);

    Uniform getUniform(const std::string& varName);
    void addTexture(const Texture &texture);
};


#endif //OPENGLGO_PROGRAM_H
