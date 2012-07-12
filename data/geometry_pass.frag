#version 330 core

in vec2 UV;
in vec3 normal_viewspace, position_viewspace;

uniform sampler2D TextureSampler;

layout (location = 0) out vec3 outposition_viewspace;
layout (location = 1) out vec3 outDiffuse;
layout (location = 2) out vec3 outnormal_viewspace;
layout (location = 3) out vec3 outUV;

void main()
{
    outDiffuse = texture(TextureSampler, UV).rgb;
    outposition_viewspace = position_viewspace;
    outnormal_viewspace = normal_viewspace;
    outUV = vec3(UV, 1);
}

