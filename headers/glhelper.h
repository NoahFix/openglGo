//
// Created by NoahFix on 2024/2/2.
//

#ifndef OPENGLGO_GLHELPER_H
#define OPENGLGO_GLHELPER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <thread>

static void getShaderSrc(std::vector<std::string> &lines, std::string &src) {
    std::string s;
    for(std::string &l:lines) {
        // Well, string.push_back() only accept char as its argument.

        s.append(l);
        src = s;
    }
}

static void readShader(const std::string &path, std::string &placeToStoreSrc) {
    // A crucial problem is that feof can only be called when you finished reading a char.
    // Call it before reading is mostly meaningless.
    /*

     问题出在你读取文件的方式上，以及在每次读取字符之前没有检查文件结束标志。`feof()` 函数在读取文件之前调用是不准确的，它只能在上一次读取操作发生后才能准确反映文件结束标志。

你可以改进代码，使用更简单、更可读的方式来读取文件，并且在读取每个字符之前检查文件结束标志。以下是改进后的代码：

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void readShader(const std::string &path, std::string &placeToStoreSrc) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << path << std::endl;
        perror("ifstream");
        exit(-1);
    }

    std::string line;
    std::vector<std::string> lines;
    std::string prefixSymbol = "#shader ";

    while (std::getline(file, line)) {
        if (line.compare(0, prefixSymbol.length(), prefixSymbol) == 0) {
            std::string shaderName = line.substr(prefixSymbol.length());
            std::cout << "Read shader: " << shaderName << std::endl;
        } else {
            lines.push_back(line);
        }
    }

    // Close the file explicitly (not necessary due to RAII, but good practice)
    file.close();

    getShaderSrc(lines, placeToStoreSrc);
}

int main() {
    std::string shaderSource;
    readShader("path/to/your/shader/file", shaderSource);
    std::cout << "Shader Source:\n" << shaderSource << std::endl;

    return 0;
}
```

这里使用了 `std::ifstream` 类来打开文件，并使用 `std::getline` 函数逐行读取文件内容。这样代码更简洁、可读，并且避免了手动处理 `feof` 的问题。

     * */

    FILE *fp = fopen(const_cast<char *>(path.c_str()), "r");
    if (fp == nullptr) {
        std::cout << "Error opening file: " << path << std::endl;
        perror("fopen");
        exit(-1);
    }

    std::string line;
    std::vector<std::string> lines;
    std::string prefixSymbol = "#shader ";

    while (!feof(fp)) {
        char buf = 0;
        fread(&buf, 1, 1, fp);
        if (feof(fp)) break;

        line.push_back(buf);
        while (buf != '\n') {
            fread(&buf, 1, 1, fp);
            if (feof(fp)) break;

            line.push_back(buf);
        }

        if (line.compare(0, prefixSymbol.length(), prefixSymbol) == 0) {
            std::string shaderName = line.substr(prefixSymbol.length() + 1, line.length() - prefixSymbol.length() - 1);
            std::cout << "Read shader: " << shaderName << std::endl;
        } else {
            lines.push_back(line);
        }
        // This sentence is vital, or it will read all the file in one "line"
        line = "";
    }

    getShaderSrc(lines, placeToStoreSrc);
}

static unsigned int compileShader(const std::string &src, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char *src1 = src.c_str();
    glShaderSource(id, 1, &src1,nullptr);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == false) {
        std::cout << "Cannot compile shader!!!" << std::endl;

        int msg_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msg_length);
        msg_length++;
        char *msg_block = (char*)alloca(msg_length);
        memset(reinterpret_cast<void *>(msg_block), 0, msg_length);
        glGetShaderInfoLog(id, msg_length, &msg_length, msg_block);
        std::cout << msg_block << std::endl;
    }

    return id;

}

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader, unsigned int *vsID = nullptr, unsigned int *fsID = nullptr) {
    unsigned int idProgram = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    if(vsID != nullptr) *vsID = vs;
    if(fsID != nullptr) *fsID = fs;

    glAttachShader(idProgram, vs);
    glAttachShader(idProgram, fs);
    glLinkProgram(idProgram);
    glValidateProgram(idProgram);
    int status;
    glGetProgramiv(idProgram, GL_VALIDATE_STATUS, &status);
    if (status == false) {
        std::cout << "Cannot validate program." << std::endl;

        int len;
        glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &len);
        len++;
        char *msg_block = (char*)alloca(len);
        memset(msg_block, 0, len);
        glGetProgramInfoLog(idProgram, len, &len, msg_block);

        std::cout << msg_block << std::endl;
    }

    return idProgram;
}

static int GLInit(GLFWwindow **window) {
    // The lack of the sentence caused crash.
    glfwInit();

    // These code is used to make glfw adapt to version 330.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(*window);
    glfwSwapInterval(500);

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

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glEnable(GL_DEPTH_TEST);

    return 0;
}

#endif //OPENGLGO_GLHELPER_H
