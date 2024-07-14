//
// Created by NoahFix on 2024/2/2.
//

#include "VertexMemoryLayout.h"
#include "glad/glad.h"
#include <exception>

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

VertexMemoryLayout VertexMemoryLayout::getPresetLayout(int layoutName) {
    VertexMemoryLayout layout;
    if(layoutName == LAYOUT_TYPE_M3DT2D) {
        layout.pushFloat(3);
        layout.pushFloat(2);
    } else {
        throw std::runtime_error("Unknown layout type");
    }
    return layout;
}



