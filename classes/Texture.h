//
// Created by NoahFix on 2024/2/9.
//

#ifndef OPENGLGO_TEXTURE_H
#define OPENGLGO_TEXTURE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GLMemoryObject.h"
#include <string>
class Program;

class Texture: public GLMemoryObject {
    friend class Program;
private:
    std::string textureUniName;
    Texture(const std::string &textureUniName, int);
public:
    Texture(char *pic_buffer, int width, int height, const std::string &textureUniName, bool alpha = true);
    Texture(const std::string &file, const std::string &textureUniName, bool alpha = true);
};


#endif //OPENGLGO_TEXTURE_H
