#version 460 core

layout(location = 0) out vec2 uv;

void main() {
    uv.x = (gl_VertexID & 1);
    uv.y = ((gl_VertexID >> 1) & 1);
    vec2 position = vec2(gl_VertexID % 2, gl_VertexID / 2) * 4.0 - 1;

    gl_Position = vec4(uv * 2 - 1, 0, 1);
} 