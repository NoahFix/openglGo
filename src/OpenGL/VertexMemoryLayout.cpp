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

    switch (layoutName) {
        case LAYOUT_TYPE_F3F2: {
            layout.pushFloat(3);
            layout.pushFloat(2);
            break;
        }

        case LAYOUT_TYPE_F3F3: {
            layout.pushFloat(3);
            layout.pushFloat(3);
            break;
        }

        case LAYOUT_TYPE_F3F3F2: {
            layout.pushFloat(3);
            layout.pushFloat(3);
            layout.pushFloat(2);
            break;
        }

        default: throw std::runtime_error("Unknown layout type");
    }
    return layout;
}



