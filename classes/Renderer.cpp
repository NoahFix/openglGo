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

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

}

void Renderer::init(IndexBuffer *ibo, Program *shader, VertexArray *vao, VertexBuffer *vbo) {
    _ibo = ibo;
    _shader = shader;
    _vao = vao;
    _vbo = vbo;

    if (_vbo != nullptr)
        _vbo->bind();

    if (_vao != nullptr)
        _vao->bind();

    if (_ibo != nullptr)
        _ibo->bind();
    if (_shader != nullptr)
        _shader->bind();
}

void Renderer::renderArrays(int count) {
    if((_shader == nullptr) || (_vao == nullptr) || (_vbo == nullptr))
        throw std::runtime_error("Uninitialized renderer! IBO shouldn't be set!");
    if (_ibo != nullptr)
        _ibo->unbind();

//    std::cout << count << std::endl;
    glDrawArrays(GL_TRIANGLES, 0, count);


}
