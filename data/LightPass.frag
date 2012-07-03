#version 330 core

in vec2 UV;

uniform sampler2D position_worldspace;
uniform sampler2D diffuse;
uniform sampler2D normal_worldspace;

out vec3 FragColor;

void main()
{
    vec2 TexCoord = gl_FragCoord.xy / gScreenSize;
    vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
    vec3 Color = texture(gColorMap, TexCoord).xyz;
    vec3 Normal = normalize(Normal);

    FragColor = vec4(Color, 1.0) * //calcpointlight\\
}
