#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;

uniform mat4 modelMatrix;

out vec3 outColor;

void main()
{
    gl_Position = modelMatrix * vec4(position, 1.0);
    outColor = inColor;
}