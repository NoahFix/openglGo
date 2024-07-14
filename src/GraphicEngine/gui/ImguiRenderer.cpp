//
// Created by NoahFix on 2024/7/14.
//
#include "ImguiRenderer.h"
#include "classes/GEInstance.h"

using namespace ImGui;

void ImguiRenderer::init() {

    IMGUI_CHECKVERSION();
    CreateContext();
    io = &ImGui::GetIO(); (void)io;

    GLFWwindow *window = GEInstance::getWindowPtr();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImguiRenderer::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

void ImguiRenderer::beginRenderer() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

void ImguiRenderer::endRenderer() {
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

