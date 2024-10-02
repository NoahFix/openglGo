//
// Created by NoahFix on 2024/10/2.
//

#ifndef OPENGLGO_HASHABLE_H
#define OPENGLGO_HASHABLE_H


class Hashable {
public:
    bool operator>(const Hashable& obj);
    Hashable();
    long hash;
    long getHash();
};


#endif //OPENGLGO_HASHABLE_H
