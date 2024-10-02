//
// Created by NoahFix on 2024/4/5.
//

#ifndef OPENGLGO_TEXTUREMANAGER_H
#define OPENGLGO_TEXTUREMANAGER_H


#include "Texture.h"
#include <vector>
#include <map>

class TextureManager {
public:
    TextureManager(const TextureManager &instance) = delete;
    TextureManager& operator=(const TextureManager &instance) = delete;
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    std::map<int, const Texture&> insertedTexturesList;
    int addTexture(const Texture& texture);
    int existTexture(const Texture &texture);
private:
    TextureManager() = default;
    int m_textureCount = 0;

};


#endif //OPENGLGO_TEXTUREMANAGER_H
