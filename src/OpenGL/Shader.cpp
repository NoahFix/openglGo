//
// Created by NoahFix on 2024/2/2.
//

#include "Shader.h"
#include "../../libraries/glhelper.h"

Shader::Shader(std::string &src, unsigned int type) {
    m_ID = compileShader(src, type);
}

Shader::~Shader() {
    glDeleteShader(m_ID);

}
