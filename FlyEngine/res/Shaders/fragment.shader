#version 330 core

in vec3 outColor;
out vec4 fragColor;

uniform vec3 colorMultiplier;

void main()
{
    fragColor = vec4(outColor * colorMultiplier, 1.0); 
}