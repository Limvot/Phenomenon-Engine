#version 330 core

in vec2 UV;
in vec3 normal, lightDirection, LightColor, eyeDirection;
in float LightPower, LightDistance;

//out vec4 FragColor;

uniform sampler2D TextureSampler;

layout (location = 0) out vec3 FragColor;

void main()
{
    vec3 eyeDirection_normalized = normalize(eyeDirection);
    vec3 lightDirection_normalized = normalize(lightDirection);
    vec3 normal_normalized = normalize(normal);

    float cosTheta = clamp(dot(normal_normalized, lightDirection_normalized), 0, 1);

    vec3 reflection = reflect(-lightDirection_normalized, normal_normalized);
    float cosReflectEye = clamp(dot(eyeDirection_normalized, reflection), 0, 1);

    vec3 AmbientColor = texture2D(TextureSampler, UV).rgb;
    vec3 DiffuseColor = texture2D(TextureSampler, UV).rgb;
    vec3 SpecularColor = texture2D(TextureSampler, UV).rgb;//vec3(1,1,1);

                //Ambiant
    vec3 Ambient = AmbientColor * vec3(0.02, 0.02, 0.02);
                //Diffuse
    vec3 Diffuse = DiffuseColor * cosTheta * LightColor * LightPower / (LightDistance * LightDistance);
                //Specular
    vec3 Specular = SpecularColor * pow(cosReflectEye, 5) * LightColor * LightPower / (LightDistance * LightDistance);

    //FragColor = vec4(Ambient + Diffuse + Specular, 1);
    FragColor = Ambient + Diffuse + Specular;
}

