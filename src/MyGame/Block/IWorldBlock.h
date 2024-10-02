//
// Created by NoahFix on 2024/8/5.
//

#ifndef OPENGLGO_IWORLDBLOCK_H
#define OPENGLGO_IWORLDBLOCK_H
#include "glm.hpp"

class IWorldBlock {
public:
    virtual ~IWorldBlock() = 0;
    virtual const glm::vec3& getPosition() = 0;
    virtual void setPosition(const glm::vec3& pos) = 0;
};

#endif //OPENGLGO_IWORLDBLOCK_H
