//
// Created by NoahFix on 2024/7/27.
//

#ifndef OPENGLGO_CHUNK_H
#define OPENGLGO_CHUNK_H
#include <array>
#include <glm.hpp>
#include <functional>
#include "defination.h"
#include "Block/AirBlock.h"
#include "Block/WorldBlock.h"

#define CHUNK_STRUCT(x, y, z, type) std::array<std::array<std::array<type, x>, y>, z>


template<int x, int y, int z, typename T> class Chunk {
public:
    T& operator()(int ix, int iy, int iz) {
        return chunk[ix][iy][iz];
    }

    Chunk() {
        foreach([this](int ix, int iy, int iz, T block) -> void {
            chunk[ix][iy][iz] = std::make_shared<WorldBlock<AirBlock>>(glm::vec3(ix, iy, iz));
        });
    }

    explicit Chunk(glm::vec3 chunkPos): Chunk() {
//        Chunk(); This sentence can't call the default constructor as you expected
        globalize(chunkPos);
    }

    void foreach(std::function<void(int, int, int, T)> callback) {
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < z; ++j) {
                for (int k = 0; k < y; ++k) {
                    callback(i, k, j, chunk[i][k][j]);
                }
            }
        }
    }

    std::array<std::array<int, 50>, 50> operator[](int n) {
        return chunk[n];
    }

    // 'y' attribute is ignored.Since the chunk doesn't consider y position
    void globalize(const glm::vec3& chunkPos) {
        chunkPosition = chunkPos;
        foreach([&chunkPos](int ix, int iy, int iz, T block) -> void {
           IWorldBlock& worldBlock = *block;
           glm::vec3 localPosition = worldBlock.getPosition();
           worldBlock.setPosition({localPosition.x + chunkPos.x,
                                        localPosition.y,
                                        localPosition.z + chunkPos.z});
        });
    }

    static int getChunkX() { return x; }
    static int getChunkY() { return y; }
    static int getChunkZ() { return z; }
private:
    glm::vec3 chunkPosition {0, 0, 0};
    CHUNK_STRUCT(x, y, z, T) chunk;

};

using GameChunk = Chunk<50, 50, 100, std::shared_ptr<IWorldBlock>>;


#endif //OPENGLGO_CHUNK_H
