#version 330 core

layout (location = 0) in vec3 position_modelspace;
layout (location = 1) in vec2 UV_in;

out vec2 UV;

void main() {

    gl_Position = vec4(position_modelspace, 1);
    UV = UV_in;
}
