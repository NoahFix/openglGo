//
// Created by NoahFix on 2024/2/14.
//

#ifndef OPENGLGO_GEINSTANCE_H
#define OPENGLGO_GEINSTANCE_H

//#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GERenderableObject.h"
#include <vector>
#include <memory>
#include <mutex>
#include "CameraObject.h"
#include "gui/ImguiRenderer.h"
#include "GERenderer.h"

struct Rect {
    int width;
    int height;
};


class GEInstance {
public:
    GEInstance(const GEInstance &instance) = delete;
    GEInstance& operator=(const GEInstance &instance) = delete;
    void setClearColor(float r, float g, float b);
    int begin(Rect windowSize, const std::string &title);

    void renderArray(GERenderableObject *object);
    static GLFWwindow* getWindowPtr();
    void renderLoop(std::function<void(void)> *dynamicTransCallback = nullptr);
    CameraObject& getCamera();

    static GEInstance& getInstance() {
        static GEInstance instance;
        return instance;
    }

private:
    GERenderer geRenderer;
    ImguiRenderer imguiRenderer;
    glm::vec3 clearColor;
    GEInstance();
    CameraObject builtInCamera;
    inline static Rect windowSize {600, 400};

//    bool beginRenderingLoop = false;
// TODO: 从这里就烂了，因为这个vector强制GLObject进行复制，从而导致多个相同的GLObject持有同样的IBO地址，在它们析构时，就会重复析构
    std::vector<GERenderableObject*> renderList;
//    std::thread&& renderingThread;
    void processInput(GLFWwindow *window, glm::vec3 &o_cameraPos, const glm::vec3 &i_vectorForward);

    static void fittingWindowResizing(GLFWwindow *_, int width, int height);
};


#endif //OPENGLGO_GEINSTANCE_H
