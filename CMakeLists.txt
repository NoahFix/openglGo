cmake_minimum_required(VERSION 3.26)
project(openglGo)

set(CMAKE_CXX_STANDARD 11)

include_directories(./glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.9/include)
include_directories(/Users/noahfix/CLionProjects/openglGo/libraries/glm)

link_directories(/opt/homebrew/Cellar/glfw/3.3.9/lib)

add_executable(openglGo
        ./glad/src/glad.c
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
        classes/Camera.h
        classes/GLInstance.h
        classes/GLInstance.cpp
        classes/GLObject.h
        classes/GLObject.cpp
        classes/Camera.cpp
        classes/TextureManager.h
        classes/TextureManager.cpp
        classes/Objects/GLCube.h
        classes/Objects/GLCube.cpp
)

target_link_libraries(
        openglGo
        glfw
        "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo"
)