//
// Created by NoahFix on 2024/2/2.
//

#include "Program.h"
#include "glad/glad.h"
#include "Texture.h"
#include "../../libraries/glhelper.h"
#include "gtc/type_ptr.hpp"
#include <string>
#include <iostream>
#include <exception>
#include "TextureManager.h"

Program::Program(const Shader& vs, const Shader& fs) {
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vs.m_ID);
    glAttachShader(m_ID, fs.m_ID);
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);

    int status;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &status);
    if (status == false) {
        std::cout << "Cannot compile shader!!!" << std::endl;

        int msg_length;
        glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &msg_length);
        msg_length++;
        char *msg_block = (char*)alloca(msg_length);
        memset(reinterpret_cast<void *>(msg_block), 0, msg_length);
        glGetShaderInfoLog(m_ID, msg_length, &msg_length, msg_block);
        std::cout << msg_block << std::endl;
    }

    // link shaders
    // check for linking errors
    if (!status) {
        std::cout << "Cannot compile shader!!!" << std::endl;

        int msg_length;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
        msg_length++;
        char *msg_block = (char*)alloca(msg_length);
        memset(reinterpret_cast<void *>(msg_block), 0, msg_length);
        glGetProgramInfoLog(m_ID, msg_length, &msg_length, msg_block);
        std::cout << msg_block << std::endl;

    }

}

void Program::bind() {
    glUseProgram(m_ID);
}

void Program::unbind() {
    glUseProgram(0);
}

Program::~Program() {
    glDeleteProgram(m_ID);

}

Uniform Program::getUniform(const std::string& varName) {
    int uniformLocation = glGetUniformLocation(m_ID, varName.c_str());
    if (uniformLocation == -1) throw std::runtime_error("Failed to get uniform: '" + varName + "'");
    return Uniform(uniformLocation);
}

unsigned int Program::getID() {
    return m_ID;
}



Program::Program(const std::string &vsFilePath, const std::string &fsFilePath) {
    std::string srcVS;
    std::string srcFS;

    readShader(vsFilePath, srcVS);
    readShader(fsFilePath, srcFS);
    Shader fragmentShader(srcFS, GL_FRAGMENT_SHADER), vertexShader(srcVS, GL_VERTEX_SHADER);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader.m_ID);
    glAttachShader(m_ID, fragmentShader.m_ID);
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);

    int status;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &status);
    if (status == false) {
        std::cout << "Cannot compile shader!!!" << std::endl;

        int msg_length;
        glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &msg_length);
        msg_length++;
        char *msg_block = (char*)alloca(msg_length);
        memset(reinterpret_cast<void *>(msg_block), 0, msg_length);
        glGetShaderInfoLog(m_ID, msg_length, &msg_length, msg_block);
        std::cout << msg_block << std::endl;
    }

    // link shaders
    // check for linking errors
    if (!status) {
        std::cout << "Cannot compile shader!!!" << std::endl;

        int msg_length;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
        msg_length++;
        char *msg_block = (char*)alloca(msg_length);
        memset(reinterpret_cast<void *>(msg_block), 0, msg_length);
        glGetProgramInfoLog(m_ID, msg_length, &msg_length, msg_block);
        std::cout << msg_block << std::endl;

    }

    bind();
    std::cout << "Bind Program mID: " << m_ID << std::endl;
}

void Program::setI(const std::string &name, int v) {
    getUniform(name).setI(v);
}

void Program::set4f(const std::string &name, int v1, int v2, int v3, int v4) {
    getUniform(name).set4f(v1, v2, v3, v4);
}

void Program::setMatrix4(const std::string &name, glm::mat4 Mat4) {
    int modelMatUni = glGetUniformLocation(this->getID(), name.c_str());
    glUniformMatrix4fv(modelMatUni, 1, GL_FALSE, glm::value_ptr(Mat4));
}

// The function is especially designed for shaders who only support to use 1 texture currently!
// So its logic is that when it detects itself already has a texture, it'll just bind the texture belonging to it to uniform.
// When it doesn't have a texture, it will add the texture to TextureManager and bind the texture to itself.
void Program::addTexture(const Texture &texture) {

    int sq;
    TextureManager& tm = TextureManager::getInstance();
    if((sq = tm.existTexture(texture)) != -1) {
        getUniform(texture.textureUniName).setI(sq);
    } else {
        int seq = tm.addTexture(texture);
        getUniform(texture.textureUniName).setI(seq);

    }
}
