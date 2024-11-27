#version 330 core

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    sampler2D height;
    float shininess;
}; 

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform Material material;
uniform vec3 baseColor;
uniform vec3 entityColor;

void main()
{    
    vec3 result = vec3(0.0);
    
    result = texture(material.diffuse, TexCoords).rgb;

    result *= baseColor;
    result *= entityColor;

    FragColor = vec4(result, 1.0);
}
