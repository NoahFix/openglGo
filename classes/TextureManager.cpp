//
// Created by NoahFix on 2024/4/5.
//

#include "TextureManager.h"
#include "Texture.h"


int TextureManager::addTexture(const Texture& texture) {
    if (m_textureCount > 15)
        throw std::runtime_error("Only 16 textures can be applied!");

    texturesIdList.push_back(texture.m_ID);
    int currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if(currentProgram == 0)
        throw std::runtime_error("Bind shader program before adding textures(Render())!");
//    std::cout << "m_textureCount = " << m_textureCount << std::endl;
    glActiveTexture(GL_TEXTURE0 + m_textureCount);
    glBindTexture(GL_TEXTURE_2D, texture.m_ID);

    // 这里返回的m_textureCount就是刚刚绑定的贴图的序号！！！！
    return m_textureCount++;
}

int TextureManager::existTexture(const Texture &texture) {
    for (int i = 0; i < texturesIdList.size(); ++i) {
        if (texturesIdList.at(i) == texture.m_ID)
            return i;
    }

    return -1;
}

//const TextureManager& getInstance() {
//    return
//}