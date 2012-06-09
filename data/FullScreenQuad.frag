#version 330 core

in vec2 UV;
//out vec4 FragColor;

uniform sampler2D renderedTexture;
uniform float time;

out vec3 color;

void main()
{
    vec3 color_non_gamma = texture2D(renderedTexture, UV + 0.009*vec2( sin(time+1024.0*UV.x), cos(time+768.0*UV.y))).rgb;
    //vec3 color_non_gamma = vec3(sin(time+1024.0*UV.x), 1, cos(time+768.0*UV.y)).rgb;
    //vec3 color_non_gamma = texture2D(renderedTexture, UV).rgb;
    color.rgb = pow(color_non_gamma.rgb, vec3(.4545));              //Gamma correction
}
