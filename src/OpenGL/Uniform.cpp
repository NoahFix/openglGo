//
// Created by NoahFix on 2024/2/2.
//

#include "Uniform.h"
#include "glad/glad.h"

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
