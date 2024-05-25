//
// Created by NoahFix on 2024/4/5.
//

#include "TextureManager.h"
#include "Texture.h"
#include <GLFW/glfw3.h>


int TextureManager::addTexture(const Texture& texture) {
    if (m_textureCount > 15)
        throw std::runtime_error("Only 16 textures can be applied!");

    int currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if(currentProgram == 0)
        throw std::runtime_error("Bind shader program before adding textures(Render())!");
//    std::cout << "m_textureCount = " << m_textureCount << std::endl;
    glActiveTexture(GL_TEXTURE0 + m_textureCount);
    glBindTexture(GL_TEXTURE_2D, texture.m_ID);

    // 这里返回的m_textureCount是下一次绑定的纹理的编号，而不是刚刚绑定完的纹理的编号。
    return m_textureCount++;
}

//const TextureManager& getInstance() {
//    return
//}