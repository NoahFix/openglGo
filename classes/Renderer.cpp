//
// Created by NoahFix on 2024/2/2.
//

#include "Renderer.h"
#include "glad/glad.h"
#include "IndexBuffer.h"
#include "Program.h"
#include "VertexArray.h"

void Renderer::render(int count) {
    if((_ibo == nullptr) || (_shader == nullptr) || (_vao == nullptr) || (_vbo == nullptr))
        throw std::runtime_error("Uninitialized renderer! ");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

}

void Renderer::init(IndexBuffer *ibo, Program *shader, VertexArray *vao, VertexBuffer *vbo) {
    _ibo = ibo;
    _shader = shader;
    _vao = vao;
    _vbo = vbo;

    _vao->bind();
    _shader->bind();
    _vbo->bind();
    _ibo->bind();
}

void Renderer::renderArrays(int count) {
    if((_shader == nullptr) || (_vao == nullptr) || (_vbo == nullptr))
        throw std::runtime_error("Uninitialized renderer! IBO shouldn't be set!");
    if (_ibo != nullptr)
        _ibo->unbind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, count);

}
