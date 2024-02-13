#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;   // Get texture from program
uniform sampler2D texture2;   // Get texture from program

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}