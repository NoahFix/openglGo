//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_RENDERER_H
#define OPENGLGO_RENDERER_H

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Program.h"
#include "IndexBuffer.h"

static IndexBuffer *_ibo = nullptr;
static Program *_shader = nullptr;
static VertexArray *_vao = nullptr;
static VertexBuffer *_vbo = nullptr;

class Renderer {
private:

public:
    static void init(IndexBuffer *ibo, Program *shader, VertexArray *vao, VertexBuffer *vbo);
    static void render(int count);
    static void renderArrays(int count);
};


#endif //OPENGLGO_RENDERER_H
