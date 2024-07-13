#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec2 TextureCoord;

out vec2 texCoord;

uniform mat4 glPosition;

void main()
{
    texCoord = TextureCoord;
    gl_Position = glPosition * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}