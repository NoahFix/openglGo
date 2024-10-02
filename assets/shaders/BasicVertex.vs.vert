#version 330 core
layout (location = 0) in vec3 aPos;

// 一定得用mat4，别用成了vec4！！

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotate;

void main()
{
    gl_Position = projection * view * model * rotate * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
