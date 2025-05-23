//
// Created by NoahFix on 2024/7/14.
//

#ifndef OPENGLGO_TRANSFORMATION_H
#define OPENGLGO_TRANSFORMATION_H

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>

class Transformation {
public:
    glm::vec3 position{};
    glm::mat4 scale{1.0f};
    glm::mat4 rotate{1.0f};
};


#endif //OPENGLGO_TRANSFORMATION_H
