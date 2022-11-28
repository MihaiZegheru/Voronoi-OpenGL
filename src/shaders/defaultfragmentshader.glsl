#version 460 core

layout(location = 0) in vec2 texCoord;

out vec4 fragColor;

void main() 
{
    // RGBA
    fragColor = vec4(texCoord, 0.5, 1);
} 