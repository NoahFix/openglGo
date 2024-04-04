//
// Created by NoahFix on 2024/2/2.
//

#include "IndexBuffer.h"
#include "glad/glad.h"
#include <iostream>

IndexBuffer::IndexBuffer(int size, char *data): size(size) {
//    std::cout << "IBO constructed: size = " << size << ", data = " << (long)data << ", current IBO addr = " << (long) this << std::endl;
    if (size == 0 || data == nullptr) {
        m_ID = 0;
        return;
    }

    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::bind() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

bool IndexBuffer::isNullIBO() {
    return !m_ID;
}

int IndexBuffer::getIndicesCount() {
    return size / sizeof(unsigned int);
}

