//
// Created by NoahFix on 2024/7/27.
//

#ifndef OPENGLGO_WORLD_H
#define OPENGLGO_WORLD_H

#include "Chunk.h"

template<int xnChunks, int znChunks> class World {
public:
    World() {
        // Generate 10 * 10 chunks
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                chunks[i][j].emplace_back(glm::vec3 {i * GameChunk::getChunkX(), 0, j * GameChunk::getChunkZ()});
            }
        }

    }


    IWorldBlock& getBlockAt(glm::vec3 pos) {
        int xChunks = (int)pos.x / GameChunk::getChunkX();
        int zChunks = (int)pos.z / GameChunk::getChunkZ();

        int xOffset = (int)pos.x % GameChunk::getChunkX();
        int yOffset = pos.y;
        int zOffset = (int)pos.z % GameChunk::getChunkZ();


        return *chunks[xChunks][zChunks](xOffset, yOffset, zOffset);
    }

    std::array<std::array<GameChunk, znChunks>, xnChunks> chunks;
};


#endif //OPENGLGO_WORLD_H
