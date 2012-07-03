#version 330 core

layout (location = 0) in vec3 position_modelspace;
uniform mat4 WVP;

void main()
{
    gl_Position = WVP * vec4(position_modelspace, 1);
}
