//
// Created by NoahFix on 2024/10/1.
//

#ifndef OPENGLGO_MATERIAL_H
#define OPENGLGO_MATERIAL_H

#include <glm.hpp>
#include "OpenGL/Texture.h"

class Material {
public:
    float ambient;
    Texture diffuse;
    Texture specular;
    float shininess;

    Material(float ambient, Texture diffuse, Texture specular, float shininess);
};


#endif //OPENGLGO_MATERIAL_H
