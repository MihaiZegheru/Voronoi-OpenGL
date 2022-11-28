#version 460 core

layout (location = 0) uniform vec2 screenRes; 
layout (location = 1) uniform vec2 seedPos; 
layout (location = 2) uniform vec4 seedColor; 

in vec2 uv;

out vec4 fragColor;

void main() {
    gl_FragDepth = length(gl_FragCoord.xy - seedPos) / length(screenRes);
    fragColor = seedColor;
} 