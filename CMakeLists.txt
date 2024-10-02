cmake_minimum_required(VERSION 3.26)
project(openglGo)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.9/include)
include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/glm)
include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/imgui)
include_directories(/Users/noahfix/CLionProjects/openglGo/src/)
include_directories(/Users/noahfix/CLionProjects/openglGo/src/GraphicEngine)
include_directories(/opt/homebrew/Cellar/assimp/5.4.2/include)
include_directories(/Users/noahfix/CLionProjects/openglGo/src/MyGame/utils)
include_directories(/Users/noahfix/CLionProjects/openglGo/src/MyGame)
include_directories()

link_directories(/opt/homebrew/Cellar/glfw/3.3.9/lib)
link_directories(/opt/homebrew/Cellar/assimp/5.4.2/lib)

file(GLOB_RECURSE SRC_SRC ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SRC_LIBRARIES ${PROJECT_SOURCE_DIR}/libraries)

set(SRC ${SRC_SRC} ${SRC_LIBRARIES} main.cpp)

add_executable(openglGo
        libraries/glad/src/glad.c
        main.cpp
        src/OpenGL/VertexBuffer.cpp
        src/OpenGL/VertexBuffer.h
        src/OpenGL/GLMemoryObject.h
        src/OpenGL/VertexArray.cpp
        src/OpenGL/VertexArray.h
        src/OpenGL/BindableObject.h
        src/OpenGL/Program.cpp
        src/OpenGL/Program.h
        src/OpenGL/Shader.cpp
        src/OpenGL/Shader.h
        src/OpenGL/Uniform.cpp
        src/OpenGL/Uniform.h
        libraries/glhelper.h
        src/OpenGL/IndexBuffer.h
        src/OpenGL/IndexBuffer.cpp
        src/OpenGL/VertexMemoryLayout.h
        src/OpenGL/VertexMemoryLayout.cpp
        src/OpenGL/Renderer.h
        src/OpenGL/Renderer.cpp
        libraries/stb_image.h
        src/OpenGL/Texture.h
        src/OpenGL/Texture.cpp
        src/GraphicEngine/classes/CameraObject.h
        src/GraphicEngine/classes/GEInstance.h
        src/GraphicEngine/classes/GEInstance.cpp
        src/GraphicEngine/classes/GERenderableObject.h
        src/GraphicEngine/classes/GERenderableObject.cpp
        src/GraphicEngine/classes/CameraObject.cpp
        src/OpenGL/TextureManager.h
        src/OpenGL/TextureManager.cpp
        src/GraphicEngine/utils/GLCube.h
        src/GraphicEngine/utils/GLCube.cpp
        src/GraphicEngine/Properties/Transformation.h
        src/GraphicEngine/Properties/Textures.h
        src/GraphicEngine/Properties/OpenGLDetails.h
        src/GraphicEngine/gui/ImguiRenderer.cpp
        libraries/imgui/imgui_demo.cpp
        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/imgui_impl_glfw.cpp
        libraries/imgui/imgui_impl_opengl3.cpp
        libraries/imgui/imgui_stdlib.cpp
        libraries/imgui/imgui_tables.cpp
        libraries/imgui/imgui_widgets.cpp
        src/GraphicEngine/classes/GEObject.h
        src/GraphicEngine/classes/GERenderer.h
        src/GraphicEngine/classes/GERenderer.cpp
        src/GraphicEngine/utils/utils.h
        src/GraphicEngine/classes/KeyboardCamera.h
        src/GraphicEngine/classes/KeyboardCamera.cpp
        src/GraphicEngine/classes/MouseCamera.h
        src/GraphicEngine/classes/MouseCamera.cpp
        src/MyGame/world/Chunk.h
        src/MyGame/utils/defination.h
        src/MyGame/world/World.h
        src/MyGame/world/World.cpp
        src/MyGame/Block/AirBlock.h
        src/MyGame/Block/AirBlock.cpp
        src/MyGame/Block/Block.h
        src/MyGame/Block/WorldBlock.h
        src/MyGame/Block/IWorldBlock.h
        src/GraphicEngine/classes/Material.h
        src/GraphicEngine/classes/Material.cpp
        src/GraphicEngine/classes/Hashable.h
        src/GraphicEngine/classes/Hashable.cpp

)


target_link_libraries(
        openglGo
        glfw
        "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo"
)