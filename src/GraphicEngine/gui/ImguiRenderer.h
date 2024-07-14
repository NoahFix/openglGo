//
// Created by NoahFix on 2024/7/14.
//

#ifndef OPENGLGO_IMGUIRENDERER_H
#define OPENGLGO_IMGUIRENDERER_H
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui.h"

class ImguiRenderer {
public:

    void init();

    void destroy();

    void beginRenderer();

    void endRenderer();
private:
    ImGuiIO* io;
};


#endif //OPENGLGO_IMGUIRENDERER_H
