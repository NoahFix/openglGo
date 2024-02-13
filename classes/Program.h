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


class Program: public GLMemoryObject, BindableObject {
private:
    int m_textureCount = 0;
public:
    Program(const Shader& vs, const Shader& fs);
    ~Program();
    unsigned int getID();
    void bind() override;
    void unbind() override;

    Uniform getUniform(const std::string& varName);
    void addTexture(const Texture &texture);
};


#endif //OPENGLGO_PROGRAM_H
