//
// Created by NoahFix on 2024/2/14.
//

#ifndef OPENGLGO_GLINSTANCE_H
#define OPENGLGO_GLINSTANCE_H

//#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GLObject.h"
#include <vector>
#include <memory>
#include <mutex>
#include "Camera.h"

struct Rect {
    int width;
    int height;
};


class GLInstance {
public:
    GLInstance(const GLInstance &instance) = delete;
    GLInstance& operator=(const GLInstance &instance) = delete;

    int begin(Rect windowSize, const std::string &title);
    void renderArray(GLObject *object);
    static GLFWwindow* getWindowPtr();
    void renderLoop(std::function<void(void)> *dynamicTransCallback = nullptr);
    void setCamera(const Camera& camera);

    static GLInstance& getInstance() {
        static GLInstance instance;
        return instance;
    }

private:
    Rect windowSize;
    const Camera *camera;

//    bool beginRenderingLoop = false;
// TODO: 从这里就烂了，因为这个vector强制GLObject进行复制，从而导致多个相同的GLObject持有同样的IBO地址，在它们析构时，就会重复析构
    std::vector<GLObject*> renderList;
    GLInstance() = default;
//    std::thread&& renderingThread;

};


#endif //OPENGLGO_GLINSTANCE_H
