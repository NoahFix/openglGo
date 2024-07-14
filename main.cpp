#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "src/OpenGL/VertexArray.h"
#include "src/OpenGL/VertexBuffer.h"
#include "src/OpenGL/Shader.h"
#include "src/OpenGL/Program.h"
#include "libraries/glhelper.h"
#include "src/OpenGL/IndexBuffer.h"
#include "src/OpenGL/VertexMemoryLayout.h"
#include "src/OpenGL/Renderer.h"
#include "libraries/stb_image.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "classes/GEInstance.h"
#include "classes/GERenderableObject.h"
#include "utils/GLCube.h"
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

    std::vector<GLCube*> cubes;

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            auto cube = new GLCube(shaderChest);
            cube->transformation.position.x = i;
            cube->transformation.position.z = j;
            cube->textures.textures.push_back(&texture2);
            cubes.push_back(cube);
        }
    }

    for (GLCube *cube:cubes) {
        glInstance.renderArray(cube);
    }

    CameraObject& camera = glInstance.getCamera();
    camera.setCameraPosition(-6, 3, -1);
    camera.lookAt(glm::vec3(0, 0, 0));
    std::function<void(void)> cb = [&glInstance]() -> void { };

    glInstance.renderLoop(&cb);
    return 0;
}