//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_VERTEXMEMORYLAYOUT_H
#define OPENGLGO_VERTEXMEMORYLAYOUT_H

#include <vector>

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
    void pushFloat(int count);
    std::vector<struct GLMemoryLayoutAttribute> getLayoutObject();
    void pushUint(int count);
    int getStride() const;
};


#endif //OPENGLGO_VERTEXMEMORYLAYOUT_H
