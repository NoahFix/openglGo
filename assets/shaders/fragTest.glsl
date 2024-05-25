#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D textureUniformSmile;   // Get texture from program
uniform sampler2D textureUniformChest;   // Get texture from program


void main()
{
    FragColor = mix(texture(textureUniformSmile, texCoord), texture(textureUniformChest, texCoord), 0.7);
}