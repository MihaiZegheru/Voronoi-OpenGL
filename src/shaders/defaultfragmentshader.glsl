#version 460 core

layout (location = 0) uniform vec2 screenRes; 
layout (location = 1) uniform vec2 seedPos; 
layout (location = 2) uniform vec4 seedColor; 

layout (location = 3) uniform float seedMarkerRadius; 
layout (location = 4) uniform vec4 seedMarkerColor; 

in vec2 uv;
out vec4 fragColor;

#define MINKOWSKI_VALUE 2


float EuclideanDistance(vec2 a, vec2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

float ManhattanDistance(vec2 a, vec2 b) {
    float dx = abs(b.x - a.x);
    float dy = abs(b.y - a.y);
    return sqrt(dx + dy);
}

float ChebyshevDistance(vec2 a, vec2 b) {
    float dx = abs(b.x - a.x);
    float dy = abs(b.y - a.y);
    return max(dx, dy);
}

float MinkowskiDistance(vec2 a, vec2 b, float p) {
    float dx = pow(abs(b.x - a.x), p);
    float dy = pow(abs(b.y - a.y), p);
    return pow(dx + dy, 1 / p);
}


void main() {
    if (length(gl_FragCoord.xy - seedPos) < seedMarkerRadius) {
        gl_FragDepth = 0;
        fragColor = seedMarkerColor;
    }
    else {
        gl_FragDepth =  MinkowskiDistance(seedPos, gl_FragCoord.xy, MINKOWSKI_VALUE) / length(screenRes);
        fragColor = seedColor;
    }

} 