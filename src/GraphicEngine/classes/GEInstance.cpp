//
// Created by NoahFix on 2024/2/14.
//

#include "GEInstance.h"
#include "../../../libraries/glhelper.h"
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include "../../OpenGL/Renderer.h"

static GLFWwindow *window = nullptr;
extern std::ostream& operator<<(std::ostream &out, glm::vec3 building);

void GEInstance::fittingWindowResizing(GLFWwindow* _, int width, int height) {
    glfwGetWindowSize(window, &windowSize.width, &windowSize.height);

}

void GEInstance::processInput(GLFWwindow *_) {
    static bool latelyPressedL = false;
    builtInCamera.processInput(_);
    // Custom keys
    // When key pressed down, work once.
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!latelyPressedL) {
            geRenderer.wireframeEnable = !geRenderer.wireframeEnable;
            latelyPressedL = true;
        }
    } else {
        latelyPressedL = false;
    }

}

int GEInstance::begin(Rect windowSize_, const std::string &title) {
    // The lack of the sentence caused crash.
    glfwInit();
    GEInstance::windowSize = windowSize_;
    // These code is used to make glfw adapt to version 410.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize.width, windowSize.height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const GLubyte *version = glGetString(GL_VERSION);
    if (version) {
        printf("OpenGL Version: %s\n", version);
    } else {
        // 处理获取版本信息失败的情况
    }
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
    #if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    // Create window with graphics context
    if (window == nullptr)
        return 1;


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetWindowSizeCallback(window, fittingWindowResizing);
    glfwSetCursorPosCallback(window, mouseCallback);
    if (!builtInCamera.displayCursor)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    imguiRenderer.init();

    return 0;

}

// renderList will be processed in  GEInstance::renderLoop()
void GEInstance::renderArray(GERenderableObject *object) {
    renderList.push_back(object);

}

// renderLoop负责每一帧画面的渲染，每轮循环会执行dynamicTransCallback函数，主要用于动态地对object做transformation
// 这里还涉及到了对不同object的贴图切换
void GEInstance::renderLoop(std::function<void(void)> *dynamicTransCallback) {
    double renderingStartTime = -1;
    double renderingEndTime = -1;
    double lastFPS = 0;
    double lastUpdateFPS = 0;

    while (!glfwWindowShouldClose(window))
    {
        renderingStartTime = glfwGetTime();
        // Game scene rendering
        glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, geRenderer.wireframeEnable ? GL_LINE : GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);

        processInput(GEInstance::getWindowPtr());

        // 注意：这里必须写 GERenderableObject &object:renderList 不能写成： GERenderableObject object:renderList 否则图像只会闪现而过！！！
        // TODO: or (GERenderableObject &object:renderList) 竟然能发生复制object？？？
        for(GERenderableObject *object:renderList) {
            if (!object->shouldRender)
                continue;
            // Draw main objects
            OpenGLDetails& glDetails = object->glDetails;
            Renderer::init(&glDetails.ibo, &glDetails.shader, &glDetails.vertexArray, &glDetails.vertexBuffer);

            // Texture 对象存储着一张贴图，Texture 由每个GLObject掌控，这是因为Texture 对象不能一生成就绑定到shader，必须在shader绑定后（也就上一行Renderer::init后）才能绑定texture对象
            object->loadAllTextures();

            glm::mat4 modelMat(1.0), viewMat(1.0), projectionMat(1.0);
            const glm::vec3 &objectPosition = object->transformation.position;
            modelMat = glm::translate(modelMat, objectPosition);
            // CameraObject moving process
            glm::vec3 lookAtPos;
            lookAtPos.z = sin(glm::radians(builtInCamera.yaw)) * cos(glm::radians(builtInCamera.pitch));
            lookAtPos.x = cos(glm::radians(builtInCamera.yaw)) * cos(glm::radians(builtInCamera.pitch));
            lookAtPos.y = sin(glm::radians(builtInCamera.pitch));
            lookAtPos = glm::normalize(lookAtPos);

            viewMat = glm::lookAt(builtInCamera.transformation.position,
                                  builtInCamera.transformation.position + lookAtPos,
                                glm::vec3(0.0f, 1.0f, 0.0f));

            projectionMat = glm::perspective(glm::radians(60.0f),float (windowSize.width) / float(windowSize.height), 0.1f, 100.0f);
            glDetails.shader.setMatrix4("model", modelMat);
            glDetails.shader.setMatrix4("view", viewMat);
            glDetails.shader.setMatrix4("projection", projectionMat);
            glDetails.shader.setMatrix4("rotate", object->transformation.rotate);

            if (glDetails.ibo.isNullIBO()) {
                int v = (int)(glDetails.vertexBuffer.size / glDetails.vertexArray.getEachVertexSize());
                Renderer::renderArrays(v);
            } else {
                int v = glDetails.ibo.getIndicesCount();
                glDrawElements(GL_TRIANGLES, v, GL_UNSIGNED_INT, 0);
            }

            if(dynamicTransCallback != nullptr)
                (*dynamicTransCallback)();
        }

        // GUI rendering
        imguiRenderer.beginRenderer();
        const glm::vec3 &position = builtInCamera.transformation.position;

        ImGui::Begin("Debugger");
        ImGui::Text("Position: (%f, %f, %f)", position.x, position.y, position.z);
        ImGui::Text("Window size: w%d, h%d", windowSize.width, windowSize.height);
        ImGui::Text("Frames per second: %f", lastFPS);
        ImGui::Text("Pitch: %f, Yaw: %f", builtInCamera.pitch, builtInCamera.yaw);

        ImGui::End();
        imguiRenderer.endRenderer();

        renderingEndTime = glfwGetTime();

        if (glfwGetTime() - lastUpdateFPS >= 0.5) {
            lastUpdateFPS = glfwGetTime();
            lastFPS = 1 / (renderingEndTime - renderingStartTime);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

    }

    imguiRenderer.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *GEInstance::getWindowPtr() {
    if (window == nullptr)
        throw std::runtime_error("Window has still not be created!");
    return window;
}

GEInstance::GEInstance(CameraObject &camera): builtInCamera(camera), clearColor(0, 0, 0) {}

CameraObject &GEInstance::getCamera() {
    return builtInCamera;
}

void GEInstance::setClearColor(float r, float g, float b) {
    clearColor = glm::vec3(r, g, b);
}

void GEInstance::clearLastTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GEInstance::registerKey(int glfw_key_type, bool isPressedKeyType, const std::function<void(void)>& callback) {

    GEInstance::registeredKey rk = {glfw_key_type, isPressedKeyType};
//    listeningKeys.insert(std::make_pair(rk, callback));
}

void GEInstance::mouseCallback(GLFWwindow *_, double xposIn, double yposIn) {
    GEInstance &instance_ = GEInstance::getInstance();
    instance_.builtInCamera.processMouse(_, xposIn, yposIn);
}

void GEInstance::beginGraphicEngin(CameraObject &camera) {
    if (instance == nullptr)
        instance = new GEInstance(camera);
    else
        throw std::runtime_error("Trial to reallocate GEInstance");
}

GEInstance::~GEInstance() {
    delete instance;
    delete &builtInCamera;
}
