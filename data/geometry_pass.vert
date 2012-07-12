#version 330 core

layout (location = 0) in vec3 position_modelspace;
layout (location = 1) in vec3 normal_modelspace;
layout (location = 2) in vec2 UV_in;

uniform mat4 M, V, MVP;

out vec2 UV;
out vec3 normal_viewspace, position_viewspace;


void main() {

    gl_Position = MVP * vec4(position_modelspace, 1);                                           //Output the position of the vertex in clip space
    UV = UV_in;                                                                                   //Pass the UVs through
    //position_worldspace = (M * vec4(position_modelspace,1)).xyz;
    position_viewspace = (V * M * vec4(position_modelspace,1)).xyz;
    //normal_worldspace = normalize((M * vec4(normal_modelspace,0)).xyz);                                                           //Pass the normalized vectors through
    normal_viewspace = normalize((V * M * vec4(normal_modelspace,0)).xyz);                                                      //This replace the above (this is for tansfer to viewspace)
}
