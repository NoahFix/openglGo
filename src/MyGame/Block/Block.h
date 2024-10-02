//
// Created by NoahFix on 2024/8/4.
//

#ifndef OPENGLGO_BLOCK_H
#define OPENGLGO_BLOCK_H


class Block {
public:
    bool isAir() const {return air;}
protected:
    bool air = false;

};


#endif //OPENGLGO_BLOCK_H
