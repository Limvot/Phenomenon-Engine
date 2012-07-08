#version 330 core

in vec2 UV;
in vec3 normal_worldspace, position_worldspace;

uniform sampler2D TextureSampler;

layout (location = 0) out vec3 outposition_worldspace;
layout (location = 1) out vec3 outDiffuse;
layout (location = 2) out vec3 outnormal_worldspace;
layout (location = 3) out vec3 outUV;

void main()
{
    outDiffuse = texture(TextureSampler, UV).rgb;
    outposition_worldspace = position_worldspace;
    outnormal_worldspace = normal_worldspace;
    outUV = vec3(UV, 1);
}

