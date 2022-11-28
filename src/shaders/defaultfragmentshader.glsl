#version 460 core

layout (location = 0) uniform vec2 screenRes; 
layout (location = 1) uniform vec2 seedPos; 
layout (location = 2) uniform vec4 seedColor; 

layout (location = 3) uniform float seedMarkerRadius; 
layout (location = 4) uniform vec4 seedMarkerColor; 

in vec2 uv;

out vec4 fragColor;

void main() {
    if (length(gl_FragCoord.xy - seedPos) < seedMarkerRadius) {
        gl_FragDepth = 0;
        fragColor = seedMarkerColor;
    }
    else {
        gl_FragDepth = length(gl_FragCoord.xy - seedPos) / length(screenRes);
        fragColor = seedColor;
    }

} 