#version 330 core

layout (location = 0) in vec3 position_modelspace;
layout (location = 2) in vec2 UV_in;

uniform mat4 MVP;

out vec2 UV;
out vec4 VertexColor;


void main() {

    gl_Position = MVP * vec4(position_modelspace, 1);
    UV = UV_in;
    VertexColor = vec4(clamp(position_modelspace, 0.0, 1.0), 1.0);
}
