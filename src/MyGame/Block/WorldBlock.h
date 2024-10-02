//
// Created by NoahFix on 2024/8/5.
//

#ifndef OPENGLGO_WORLDBLOCK_H
#define OPENGLGO_WORLDBLOCK_H

#include "glm.hpp"
#include "Block/IWorldBlock.h"

template<typename T> class WorldBlock: public T, public IWorldBlock {
public:
    using T::T;     // C++ 12 new feature
    explicit WorldBlock(glm::vec3 position): position(position), T() {}

    const glm::vec3 & getPosition() override {
        return position;
    }

    void setPosition(const glm::vec3 &pos) override {
        position = pos;
    }

private:
    glm::vec3 position {0, 0, 0};

};


#endif //OPENGLGO_WORLDBLOCK_H
