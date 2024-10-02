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
#include "utils/utils.h"
#include "classes/KeyboardCamera.h"
#include "classes/MouseCamera.h"

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
    GEInstance::beginGraphicEngin(*new KeyboardCamera());
    GEInstance &glInstance = GEInstance::getInstance();
    glInstance.begin({800, 600}, "Hello glPackage");
//    glInstance.setClearColor(0.1, 0.6, 1);
//    glfwSetCursorPosCallback(GEInstance::getWindowPtr(), mouse_callback);


    Program lightBlockShader("assets/shaders/light/LightShaderVert.glsl", "assets/shaders/light/LightShaderFrag.glsl");
    Program opticalBlockShader("assets/shaders/light/OpticalObjectVert.glsl", "assets/shaders/light/OpticalObjectFrag.glsl");
    //    Texture texture2("assets/pictures/bedrock.png", "textureUniformChest", true);
    //    glInstance.clearLastTexture();

    VertexMemoryLayout opticalObjectLayout;
    opticalObjectLayout.pushFloat(3);   // position (xyz)
    GLCube lightCube(lightBlockShader, opticalObjectLayout);
    utils::transform(lightCube, 3, 2, 2);

    GLCube opticalBlock(opticalBlockShader, true);

    CameraObject& camera = glInstance.getCamera();
    Uniform u_lightPosition = opticalBlockShader.getUniform("lightPosition");
    Uniform u_viewPosition = opticalBlockShader.getUniform("viewPosition");
    const glm::vec3& lightPosition = lightCube.transformation.position;
    u_lightPosition.setVector3(lightPosition);
    u_viewPosition.setVector3(camera.transformation.position);

    Texture textureBlock("assets/pictures/container2.png", "material.diffuse");
    Texture textureBlockSpecular("assets/pictures/container2_specular.png", "material.specular");
    Material cooperMaterial(0.3, textureBlock, textureBlockSpecular, 60.0);
    utils::applyMaterial(opticalBlockShader, cooperMaterial);
    glInstance.renderArray(&lightCube);
    glInstance.renderArray(&opticalBlock);
    camera.setCameraPosition(-6, 3, -1);

//    Program shaderCommon("assets/shaders/BasicVertex.vs.vert", "assets/shaders/BasicFragment.fs.frag");
//    GLCube cube(shaderCommon);
//    cube.transformation.position = {0, 0, 0};
//    cube.transformation.rotate = glm::rotate(cube.transformation.rotate, glm::radians(2.0f), glm::vec3(0.0, 0.0, 1.0));
//    glInstance.renderArray(&cube);
    std::function<void(void)> cb = [&u_viewPosition, &camera, &opticalBlock]() -> void {
        u_viewPosition.setVector3(camera.transformation.position);
        auto trans = opticalBlock.transformation.position;
        opticalBlock.transformation.rotate = glm::rotate(opticalBlock.transformation.rotate, glm::radians(1.0f), glm::vec3(0, 1.0, 0.0));

    };

    glInstance.renderLoop(&cb);
    return 0;
}