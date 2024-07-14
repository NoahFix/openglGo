//
// Created by NoahFix on 2024/2/14.
//

#ifndef OPENGLGO_GERENDERABLEOBJECT_H
#define OPENGLGO_GERENDERABLEOBJECT_H

#include "VertexBuffer.h"
#include <vector>
#include "VertexArray.h"
#include "glm.hpp"
#include "Program.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "GraphicEngine/Properties/Transformation.h"
#include "GraphicEngine/Properties/OpenGLDetails.h"
#include "GraphicEngine/Properties/Textures.h"
#include "GEObject.h"

class GEInstance;

class GERenderableObject: GEObject {
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
