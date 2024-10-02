//
// Created by NoahFix on 2024/10/2.
//

#include "Hashable.h"

long Hashable::getHash() {
    return (long)this;
}

Hashable::Hashable() {
    hash = getHash();
}

bool Hashable::operator>(const Hashable &obj) {
    return this->hash > obj.hash;
}
