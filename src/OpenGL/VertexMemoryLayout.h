//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_VERTEXMEMORYLAYOUT_H
#define OPENGLGO_VERTEXMEMORYLAYOUT_H

#include <vector>
#define LAYOUT_TYPE_M3DT2D 0

struct GLMemoryLayoutAttribute {
    int size;
    unsigned int type;
    bool normalized;
    unsigned long lengthOfAttribute;
//    size_t stride;
//    unsigned int *pointer;
};

class VertexMemoryLayout {
private:
    int m_Stride = 0;
    std::vector<struct GLMemoryLayoutAttribute> attributes;
public:
    static VertexMemoryLayout getPresetLayout(int layoutName);

    void pushFloat(int count);
    std::vector<struct GLMemoryLayoutAttribute> getLayoutObject() const;
    void pushUint(int count);
    int getStride() const;
};


#endif //OPENGLGO_VERTEXMEMORYLAYOUT_H
