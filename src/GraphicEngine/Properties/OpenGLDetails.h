//
// Created by NoahFix on 2024/7/14.
//

#include "../../OpenGL/IndexBuffer.h"
#include "../../OpenGL/Program.h"
#include "../../OpenGL/VertexArray.h"

class OpenGLDetails {
public:
    OpenGLDetails(int size, char *vertexData, const Program& shader, int sizeIBO, char *iboBuffer): vertexBuffer(size, vertexData), shader(shader), ibo(sizeIBO, iboBuffer) {

    }

    IndexBuffer ibo;
    Program shader;
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
};