#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec3 normal;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 outColor;
out vec3 fragPos; 
out vec2 outUV;
out vec3 outNormal;


void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    fragPos = vec3(modelMatrix * vec4(position, 1.0));
    outColor = color;
    outUV = UV;
    outNormal = mat3(transpose(inverse(modelMatrix))) * normal;  ;
    //outNormal = normal;  
}