#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoord;

out vec3 pointNormal;
out vec3 pointPosition;
out mat4 model_;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotate;

void main()
{
    pointPosition = (model * rotate * vec4(aPos, 1.0)).xyz;
    gl_Position =  projection * view * model * rotate * vec4(aPos, 1.0);
    pointNormal = (rotate * vec4(normal, 1.0)).xyz;
    model_ = model;
    texCoord = textCoord;
}