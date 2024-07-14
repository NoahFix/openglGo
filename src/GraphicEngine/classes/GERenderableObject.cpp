//
// Created by NoahFix on 2024/2/14.
//

#include "GERenderableObject.h"

#include <utility>
#include "gtc/type_ptr.hpp"

GERenderableObject::GERenderableObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout)
: glDetails(size, vertexData, shader, 0, nullptr) {
    transformation.position.x = 0;
    transformation.position.y = 0;
    transformation.position.z = 0;

    glDetails.vertexArray.addVertexBufferObject(glDetails.vertexBuffer, layout);
}

GERenderableObject::GERenderableObject(char *vertexData, int size, const Program &shader, const VertexMemoryLayout &layout, char *iboBuffer, int sizeIBO)
    : glDetails(size, vertexData, shader, sizeIBO, iboBuffer) {
    transformation.position.x = 0;
    transformation.position.y = 0;
    transformation.position.z = 0;

    glDetails.vertexArray.addVertexBufferObject(glDetails.vertexBuffer, layout);
    // 这里你又遇到了一个内存问题，这句代码原来是这么写的：
    // this->iboBuffer = IndexBuffer(sizeIBO, iboBuffer);
    // 由于右值是个临时对象，所以语句结束后就会被析构，ibo就会解绑。这就是深浅拷贝的问题

}

//
//GERenderableObject::GERenderableObject(const GERenderableObject &v): shader(v.shader), vertexArray(v.vertexArray), worldPosition(v.worldPosition),
//                                       vertexBuffer(v.vertexBuffer),ibo(0, nullptr),render_count(v.render_count) {
//
//}

GERenderableObject::GERenderableObject(char *vertexData, int size, const Program &&shader, const VertexMemoryLayout &layout)
: glDetails(size, vertexData, shader, 0, nullptr) {
    transformation.position.x = 0;
    transformation.position.y = 0;
    transformation.position.z = 0;

    glDetails.vertexArray.addVertexBufferObject(glDetails.vertexBuffer, layout);
}

void GERenderableObject::addTexture(const Texture &texture) {
    // TODO: 这个取得地址应该是Texture对象的地址，还是texture引用的地址？
    this->textures.textures.push_back(&texture);
}

void GERenderableObject::loadAllTextures() {
    if(!textures.textures.empty()) {
        for(const Texture *tex:textures.textures) {
            // TODO：警告：OpenGL的texture是全局的存在，而不是一个shader有16个材质槽位，而是整个OpenGL只有16个槽位。
            glDetails.shader.addTexture(*tex);
//                    object->textures.pop_back();
        }
    }
}
