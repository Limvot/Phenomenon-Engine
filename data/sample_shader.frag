#version 330 core

in vec2 UV;
in vec4 VertexColor;

out vec4 FragColor;

uniform sampler2D TextureSampler;

void main()
{
    FragColor = vec4(texture2D(TextureSampler, UV).rgb, 1) + VertexColor;
    //FragColor = VertexColor;
}

