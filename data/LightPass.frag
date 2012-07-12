#version 330 core

uniform vec2 screenSize;

uniform float LightPower;
uniform vec3 DiffuseColor, AmbientColor, SpecularColor, LightPosition, CameraPosition;

uniform sampler2D position_viewspace;
uniform sampler2D diffuse;
uniform sampler2D normal_viewspace;

out vec3 FragColor;

void main()
{
    vec2 TexCoord = gl_FragCoord.xy / screenSize;
    vec3 ViewPos = texture2D(position_viewspace, TexCoord).xyz;
    vec3 Color = texture2D(diffuse, TexCoord).xyz;
    vec3 Normal = normalize(texture2D(normal_viewspace, TexCoord).xyz);

    vec3 lightDir = normalize(LightPosition - ViewPos);
    vec3 eyeDir = normalize(CameraPosition-ViewPos);
    vec3 Reflect = reflect(-lightDir, Normal);
    float lightDistance = distance(LightPosition, ViewPos);

    float cosTheta = clamp( dot( Normal, lightDir ), 0,1 );

    float cosAlpha = clamp( dot (eyeDir, Reflect), 0,1 );


    //Color = vec3(1,1,1);

    FragColor = (Color * DiffuseColor * cosTheta * LightPower / (lightDistance * lightDistance))  //Diffuse
                + (Color * AmbientColor)                                                          //Ambient
                + (Color * SpecularColor * pow(cosAlpha, 5) / (lightDistance * lightDistance));   //Specular

    //Color = vec3(1,1,1);
    //FragColor = (Color * SpecularColor * pow(cosAlpha, 5) / (lightDistance * lightDistance));   //Specular
    //FragColor = (Color * DiffuseColor * cosTheta * LightPower / (lightDistance * lightDistance));  //Diffuse
    //FragColor = Normal;
    //FragColor = WorldPos;
}
