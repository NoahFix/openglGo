//
// Created by NoahFix on 2024/2/2.
//

#include "VertexArray.h"
#include "glad/glad.h"

void VertexArray::bind() {
    glBindVertexArray(m_ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::addVertexBufferObject(VertexBuffer &vbo, const VertexMemoryLayout &memLayout) {
    vbo.bind();
    this->bind();

    int index = 0;
    for(struct GLMemoryLayoutAttribute &attribute:memLayout.getLayoutObject()) {
        // index: define the elements'(also called 'attributes') order in memory.E.g. index 0 may mean position and index 1 may mean normals
        // size: For example, if 'type' is set like GL_FLOAT, and then 'size' means the number of floats in each vertex.Here we have 2 floats to express a point in 2D space
        // stride: size of each vertex, used for offsetting between vertices.
        // pointer: suggesting the offset value of the attribute you're setting here(such as vertices) in a vertex memory.Because a vertex can contain many attributes such as vertices, normals...
        glVertexAttribPointer(index, attribute.size, attribute.type, attribute.normalized, memLayout.getStride(), (const void *)offset);
        glEnableVertexAttribArray(index);

        offset += attribute.lengthOfAttribute;
        index ++;
    }

}

unsigned long VertexArray::getEachVertexSize() const {
    return offset;
}
