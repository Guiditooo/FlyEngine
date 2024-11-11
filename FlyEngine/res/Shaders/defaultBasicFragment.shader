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

void main()
{    
    FragColor = texture(material.diffuse, TexCoords);
}
