#version 330 core

out vec4 FragColor;
  
in vec3 FragPos;
in vec3 Normal;
in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D theTexture;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    //FragColor = vec4(outColor, 1.0);
    //FragColor = vec4(TexCoord, 0.0, 1.0);
    //FragColor = texture(theTexture, TexCoord);
    //FragColor = vec4(1.0);
}