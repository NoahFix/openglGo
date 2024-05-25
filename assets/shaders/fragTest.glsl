#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D textureUniform;   // Get texture from program

void main()
{
    FragColor = texture(textureUniform, texCoord);
}