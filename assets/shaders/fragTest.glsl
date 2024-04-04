#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D textureUniform;   // Get texture from program
uniform sampler2D textureChest;   // Get texture from program


void main()
{
    FragColor = mix(texture(textureUniform, texCoord), texture(textureChest, texCoord), 0.2);
}