//
// Created by NoahFix on 2024/7/16.
//

#include "classes/GEObject.h"
#include "classes/Material.h"
#include "classes/GERenderableObject.h"

namespace utils {
    void transform(GEObject& obj, float x, float y, float z) {
        obj.transformation.position.x = x;
        obj.transformation.position.y = y;
        obj.transformation.position.z = z;
    }

    void applyMaterial(Program &shader, const Material &material) {
        Uniform u_material_ambient = shader.getUniform("material.ambient");
        Uniform u_material_shininess = shader.getUniform("material.shininess");

        u_material_ambient.set1f(material.ambient);
        shader.addTexture(material.diffuse);
        shader.addTexture(material.specular);
        u_material_shininess.set1f(material.shininess);
    }
}