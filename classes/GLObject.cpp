//
// Created by NoahFix on 2024/2/14.
//

#include "GLObject.h"

#include <utility>
#include <gtc/type_ptr.hpp>


GLObject::GLObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout)
: vertexBuffer(size, vertexData), shader(shader), ibo(0, nullptr) {
    worldPosition.x = 0;
    worldPosition.y = 0;
    worldPosition.z = 0;

    vertexArray.addVertexBufferObject(vertexBuffer, layout);
}

glm::vec3 GLObject::getPosition() {
    return worldPosition;
}

void GLObject::setPosition(float x, float y, float z) {
    worldPosition.x = x;
    worldPosition.y = y;
    worldPosition.z = z;
}

GLObject::GLObject(char *vertexData, int size, const Program &shader, const VertexMemoryLayout &layout, char *iboBuffer, int sizeIBO)
    :vertexBuffer(size, vertexData), shader(shader), ibo(sizeIBO, iboBuffer) {
    worldPosition.x = 0;
    worldPosition.y = 0;
    worldPosition.z = 0;

    vertexArray.addVertexBufferObject(vertexBuffer, layout);
    // 这里你又遇到了一个内存问题，这句代码原来是这么写的：
    // this->iboBuffer = IndexBuffer(sizeIBO, iboBuffer);
    // 由于右值是个临时对象，所以语句结束后就会被析构，ibo就会解绑。这就是深浅拷贝的问题

}

//
//GLObject::GLObject(const GLObject &v): shader(v.shader), vertexArray(v.vertexArray), worldPosition(v.worldPosition),
//                                       vertexBuffer(v.vertexBuffer),ibo(0, nullptr),render_count(v.render_count) {
//
//}

GLObject::GLObject(char *vertexData, int size, const Program &&shader, const VertexMemoryLayout &layout)
: vertexBuffer(size, vertexData),shader(shader), ibo(0, nullptr) {
    worldPosition.x = 0;
    worldPosition.y = 0;
    worldPosition.z = 0;

    vertexArray.addVertexBufferObject(vertexBuffer, layout);
}

void GLObject::addTexture(const Texture &texture) {
    // TODO: 这个取得地址应该是Texture对象的地址，还是texture引用的地址？
    this->textures.push_back(&texture);
}

void GLObject::setMatrix4(glm::mat4 mat4, const std::string &matUniform) {
    matrix4 = mat4;
    this->mat4Uniform = matUniform;
}

void GLObject::setRotate(float degree, glm::vec3 axis) {
    this->rotate = glm::rotate(this->rotate, glm::radians(degree), axis);
}
