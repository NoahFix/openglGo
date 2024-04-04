//
// Created by NoahFix on 2024/2/2.
//

#include "VertexMemoryLayout.h"
#include "glad/glad.h"

void VertexMemoryLayout::pushFloat(int count) {
    attributes.push_back({count, GL_FLOAT, false, (count * sizeof(float))});

    m_Stride += sizeof(float) * count;
}

void VertexMemoryLayout::pushUint(int count) {
    attributes.push_back({count, GL_UNSIGNED_INT, false, (count * sizeof(float))});

    m_Stride += sizeof(unsigned int) * count;
}

int VertexMemoryLayout::getStride() const {

    return m_Stride;
}

std::vector<struct GLMemoryLayoutAttribute> VertexMemoryLayout::getLayoutObject() const {
    return attributes;
}
