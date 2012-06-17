#version 330 core

layout (location = 0) in vec3 position_modelspace;
layout (location = 1) in vec3 normal_modelspace;
layout (location = 2) in vec2 UV_in;

uniform mat4 M, V, MVP;
uniform vec3 lightPosition_worldspace, LightColor_in;
uniform float LightPower_in;

out float LightPower, LightDistance;
out vec2 UV;
out vec3 LightColor, normal, lightDirection, eyeDirection;


void main() {

    gl_Position = MVP * vec4(position_modelspace, 1);                                           //Output the position of the vertex in clip space
    UV = UV_in;                                                                                   //Pass the UVs through

    vec3 normal_cameraspace = (V * M * vec4(normal_modelspace,0)).xyz;                           //Here we transform everything to camera space
    vec3 lightPosition_cameraspace = (V * vec4(lightPosition_worldspace,1)).xyz;
    vec3 vertexPosition_cameraspace = (V * M * vec4(position_modelspace, 1)).xyz;

    vec3 eyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;                    //The eye direction (from vertex to camera) is the opposite of the vertex position (which is a vector from the camera (at the origin) to the vertex)
    vec3 lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;       //The vector from the vertex to the light is the addition of the light position and the eye direction. Draw it out, it works.

    LightDistance = distance(lightPosition_cameraspace, vertexPosition_cameraspace);             //Output the distance between the vertex and the light.

    normal = normalize(normal_cameraspace);                                                           //Pass the normalized vectors through
    lightDirection = normalize(lightDirection_cameraspace);

    eyeDirection = normalize(eyeDirection_cameraspace);

    LightColor = LightColor_in;                                                                    //Pass the LightColor and the LightPower through as well
    LightPower = LightPower_in;
}
