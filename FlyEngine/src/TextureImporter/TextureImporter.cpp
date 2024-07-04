#include "TextureImporter.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace FlyEngine
{

	namespace Importers
	{


		Texture* TextureImporter::LoadTexture(const char* path)
		{
            unsigned int textureID;
            glGenTextures(1, &textureID);

            //stbi_set_flip_vertically_on_load(1); Fiajte si es necesario
            int width, height, bpp;
            unsigned char* localBuffer = stbi_load(path, &width, &height, &bpp, 0);

            if (!localBuffer) {
                std::cerr << "Error loading texture: " << path << std::endl;
                stbi_image_free(localBuffer);
                return new Texture(0, 0, 0, "");
            }

            GLenum format;
            if (bpp == 1)
                format = GL_RED;
            else if (bpp == 3)
                format = GL_RGB;
            else if (bpp == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(localBuffer);

            std::cout << "\nTexture ID=" << textureID << " Successfully Loaded!\n";

            return new Texture(textureID, width, height, path);
		}

	}
}
