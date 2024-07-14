#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "classes/VertexArray.h"
#include "classes/VertexBuffer.h"
#include "classes/Shader.h"
#include "classes/Program.h"
#include "headers/glhelper.h"
#include "classes/IndexBuffer.h"
#include "classes/VertexMemoryLayout.h"
#include "classes/Renderer.h"
#include "libraries/stb_image.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "classes/GEInstance.h"
#include "classes/GERenderableObject.h"
#include "classes/Objects/GLCube.h"
// 返回ostream是为了能够链式调用
// ostream& 是为了保证传入 cout 时不会发拷贝，而是传入地址，否则就没法返回cout了，也就不能实现链式调用
std::ostream& operator<<(std::ostream &out, glm::vec3 building) {
    out << "(" << building.x << ", " << building.y << ", " << building.z << ")";
    return out;
}

// This is a  plane
float vertices[] = {
        0.0, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

int main() {
    GEInstance &glInstance = GEInstance::getInstance();
    glInstance.begin({800, 600}, "Hello glPackage");
    glInstance.setClearColor(0.1, 0.6, 1);
//    glfwSetCursorPosCallback(GEInstance::getWindowPtr(), mouse_callback);


    Program shaderChest = Program("assets/shaders/vertTest.glsl", "assets/shaders/singleTextureFrag.glsl");
    Texture texture2("assets/pictures/bedrock.png", "textureUniformChest", true);

    GLCube cubeLight(shaderChest);
    cubeLight.textures.textures.push_back(&texture2);

    glInstance.renderArray(&cubeLight);
    CameraObject& camera = glInstance.getCamera();
    camera.setCameraPosition(-6, 3, -1);
    camera.lookAt(glm::vec3(0, 0, 0));
    std::function<void(void)> cb = [&glInstance]() -> void { };

    glInstance.renderLoop(&cb);
    return 0;
}