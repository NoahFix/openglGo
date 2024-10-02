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
#include <map>
#include "world/Chunk.h"
#include "world/World.h"

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

    void registerKey(int glfw_key_type, bool isPressedKeyType, const std::function<void(void)>& callback);
    void clearLastTexture();
    void renderArray(GERenderableObject *object);
    static GLFWwindow* getWindowPtr();
    void renderLoop(std::function<void(void)> *dynamicTransCallback = nullptr);
    CameraObject& getCamera();

    static void beginGraphicEngin(CameraObject &camera);

    static GEInstance& getInstance() {
//        static GEInstance instance;
        if (instance == nullptr)
            throw std::runtime_error("Uninitialized GEInstance");
        return *instance;
    }

    struct registeredKey {
        int keyID;
        bool isPressedKey;
    };

    ~GEInstance();
private:
    inline static GEInstance *instance = nullptr;
    std::map<struct registeredKey, std::function<void(void)>> listeningKeys;

    GERenderer geRenderer;
    ImguiRenderer imguiRenderer{};
    glm::vec3 clearColor;
    explicit GEInstance(CameraObject &camera);
    CameraObject &builtInCamera;
    inline static Rect windowSize {600, 400};

//    bool beginRenderingLoop = false;
// TODO: 从这里就烂了，因为这个vector强制GLObject进行复制，从而导致多个相同的GLObject持有同样的IBO地址，在它们析构时，就会重复析构
    std::vector<GERenderableObject*> renderList;
//    std::thread&& renderingThread;
    void processInput(GLFWwindow *window);
    static void fittingWindowResizing(GLFWwindow *_, int width, int height);
    static void mouseCallback(GLFWwindow* _, double xposIn, double yposIn);
};


#endif //OPENGLGO_GEINSTANCE_H
