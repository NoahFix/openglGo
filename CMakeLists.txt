cmake_minimum_required(VERSION 3.26)
project(openglGo)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.9/include)
include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/glm)
include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/imgui)
include_directories(/Users/noahfix/CLionProjects/openglGo/classes/GraphicEngine)

link_directories(/opt/homebrew/Cellar/glfw/3.3.9/lib)

add_executable(openglGo
        libraries/glad/src/glad.c
        main.cpp
        classes/VertexBuffer.cpp
        classes/VertexBuffer.h
        classes/GLMemoryObject.h
        classes/VertexArray.cpp
        classes/VertexArray.h
        classes/BindableObject.h
        classes/Program.cpp
        classes/Program.h
        classes/Shader.cpp
        classes/Shader.h
        classes/Uniform.cpp
        classes/Uniform.h
        headers/glhelper.h
        classes/IndexBuffer.h
        classes/IndexBuffer.cpp
        classes/VertexMemoryLayout.h
        classes/VertexMemoryLayout.cpp
        classes/Renderer.h
        classes/Renderer.cpp
        libraries/stb_image.h
        classes/Texture.h
        classes/Texture.cpp
        classes/CameraObject.h
        classes/GEInstance.h
        classes/GEInstance.cpp
        classes/GERenderableObject.h
        classes/GERenderableObject.cpp
        classes/CameraObject.cpp
        classes/TextureManager.h
        classes/TextureManager.cpp
        classes/Objects/GLCube.h
        classes/Objects/GLCube.cpp
        classes/GraphicEngine/Properties/Transformation.h
        classes/GraphicEngine/Properties/Textures.h
        classes/GraphicEngine/Properties/OpenGLDetails.h
        classes/gui/ImguiRenderer.cpp
        libraries/imgui/imgui_demo.cpp
        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/imgui_impl_glfw.cpp
        libraries/imgui/imgui_impl_opengl3.cpp
        libraries/imgui/imgui_stdlib.cpp
        libraries/imgui/imgui_tables.cpp
        libraries/imgui/imgui_widgets.cpp
        classes/GEObject.h
        classes/GraphicEngine/Properties/Camera.h
)

target_link_libraries(
        openglGo
        glfw
        "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo"
)