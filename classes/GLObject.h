//
// Created by NoahFix on 2024/2/14.
//

#ifndef OPENGLGO_GLOBJECT_H
#define OPENGLGO_GLOBJECT_H

#include "VertexBuffer.h"
#include <vector>
#include "VertexArray.h"
#include "glm.hpp"
#include "Program.h"
#include "Texture.h"
#include "IndexBuffer.h"
class GLInstance;

class GLObject {
    friend class GLInstance;
public:
    void loadAllTextures();
    GLObject(const GLObject &v);

    GLObject(char *vertexData, int size, const Program &&shader, const VertexMemoryLayout &layout);
    GLObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout);
    GLObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout, char *iboBuffer, int sizeIBO);
    void addTexture(const Texture &texture);
    void setMatrix4(glm::mat4 mat4, const std::string &matUniform);


    glm::vec3 getPosition();
    void setPosition(float x, float y, float z);
    void addRotate(float degree, glm::vec3 axis);
private:
    glm::mat4 rotate{1.0f};
    glm::mat4 matrix4{1.0f};
    std::string mat4Uniform;

    std::vector<const Texture*> textures;
    IndexBuffer ibo;
    Program shader;
    int render_count = 0;
    glm::vec3 worldPosition;
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;

};


#endif //OPENGLGO_GLOBJECT_H
