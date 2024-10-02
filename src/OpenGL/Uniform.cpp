//
// Created by NoahFix on 2024/2/2.
//

#include "Uniform.h"
#include "glad/glad.h"
#include <iostream>

Uniform::Uniform(int uniformLocation) {
    id = uniformLocation;
}

void Uniform::set4f(float v1, float v2, float v3, float v4) {
    glUniform4f(id, v1, v2, v3, v4);
}

void Uniform::setI(int i) {
    glUniform1i(id, i);

}

int Uniform::getID() {
    return id;
}

void Uniform::set3f(float v1, float v2, float v3) {
    glUniform3f(id, v1, v2, v3);
}

void Uniform::setVector3(const glm::vec3 &vec) {
    set3f(vec.x, vec.y, vec.z);
}

void Uniform::set1f(float v1) {
    glUniform1f(id, v1);

}


