//
// Created by NoahFix on 2024/10/1.
//

#include "Material.h"

#include <utility>

Material::Material(float ambient, Texture diffuse, Texture specular, float shininess)
    : ambient(ambient), diffuse(std::move(diffuse)), specular(std::move(specular)), shininess(shininess)
{
}
