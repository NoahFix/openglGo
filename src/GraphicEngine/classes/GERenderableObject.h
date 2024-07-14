//
// Created by NoahFix on 2024/2/14.
//

#ifndef OPENGLGO_GERENDERABLEOBJECT_H
#define OPENGLGO_GERENDERABLEOBJECT_H

#include "../../OpenGL/VertexBuffer.h"
#include <vector>
#include "../../OpenGL/VertexArray.h"
#include "glm.hpp"
#include "../../OpenGL/Program.h"
#include "../../OpenGL/Texture.h"
#include "../../OpenGL/IndexBuffer.h"
#include "Properties/Transformation.h"
#include "Properties/OpenGLDetails.h"
#include "Properties/Textures.h"
#include "GEObject.h"

class GEInstance;

class GERenderableObject: public GEObject {
    friend class GEInstance;
public:
    GERenderableObject(char *vertexData, int size, const Program &&shader, const VertexMemoryLayout &layout);
    GERenderableObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout);
    GERenderableObject(char *vertexData, int size, const Program& shader, const VertexMemoryLayout& layout, char *iboBuffer, int sizeIBO);

    Textures textures;
private:
    OpenGLDetails glDetails;
    void loadAllTextures();
    void addTexture(const Texture &texture);
};


#endif //OPENGLGO_GERENDERABLEOBJECT_H
