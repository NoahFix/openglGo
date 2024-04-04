//
// Created by NoahFix on 2024/2/1.
//

#include "VertexBuffer.h"

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind() {
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_ID);
}

VertexBuffer::VertexBuffer(unsigned long size, char *data) : GLMemoryObject() {
    this->size = size;
    glGenBuffers(1, &m_ID);
    // Don't invoke virtual methods in constructors: Just add 'final' to the class declare, suggesting that the class won't be a base class.
    this->bind();
    // Basically, vertices' buffer don't have any meanings,it's just a block of memory.By setting vertex attribute, we can give them meanings.
    // It's necessary to bind vbo to slot before filling data!
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//    this->unbind();

}

