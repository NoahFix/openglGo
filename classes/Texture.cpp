//
// Created by NoahFix on 2024/2/9.
//

#include "Texture.h"
#include "../libraries/stb_image.h"
// TODO：Texture没有析构函数，但是盲目加上可能出现问题
Texture::Texture(char *pic_buffer, int width, int height, const std::string &textureUniName, bool alpha): Texture(textureUniName, 0) {
    glGenTextures(1, &m_ID);
    // Put our texture into its slot.
    glBindTexture(GL_TEXTURE_2D, m_ID);

    // 为当前绑定的纹理对象设置环绕
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置在纹理被 放大 和 缩小 时使用的处理方式（纹理过滤）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, alpha?GL_RGBA:GL_RGB, width, height, 0, alpha?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, pic_buffer);
    glGenerateMipmap(GL_TEXTURE_2D);

}

Texture::Texture(const std::string &file, const std::string &textureUniName, bool alpha): Texture(textureUniName, 0) {
    fileName = file;
    glGenTextures(1, &m_ID);
    // Put our texture into its slot.
    // The sentence may be necessary!
    glBindTexture(GL_TEXTURE_2D, m_ID);

    // 为当前绑定的纹理对象设置环绕
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置在纹理被 放大 和 缩小 时使用的处理方式（纹理过滤）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width1, height1, nrChannels1;
    unsigned char *data = stbi_load(file.c_str(), &width1, &height1, &nrChannels1, 0);
    // 加载并生成纹理
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, alpha?GL_RGBA:GL_RGB, width1, height1, 0, alpha?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load image");
    }
    stbi_image_free(data);

}

Texture::Texture(const std::string &textureUniName, int) : GLMemoryObject() {
    this->textureUniName = textureUniName;

}

std::string Texture::getFilePath() const {
    return fileName;
}
