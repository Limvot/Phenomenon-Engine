#version 330 core

uniform vec2 screenSize;

uniform float LightPower;
uniform vec3 LightColor, LightPosition, CameraPosition;

uniform sampler2D position_worldspace;
uniform sampler2D diffuse;
uniform sampler2D normal_worldspace;

out vec3 FragColor;

void main()
{
    vec2 TexCoord = gl_FragCoord.xy / screenSize;
    vec3 WorldPos = texture2D(position_worldspace, TexCoord).xyz;
    vec3 Color = texture2D(diffuse, TexCoord).xyz;
    vec3 Normal = normalize(texture2D(normal_worldspace, TexCoord).xyz);

    vec3 lightDir = LightPosition - WorldPos;
    vec3 eyeDir = normalize(CameraPosition-WorldPos);
    float lightDistance = distance(LightPosition, WorldPos);

    float cosTheta = clamp( dot( Normal, lightDir ), 0,1 );

    FragColor = Color * LightColor * cosTheta * LightPower / (lightDistance * lightDistance);
}
