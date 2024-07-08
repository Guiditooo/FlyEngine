#include "TextureImporter.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace FlyEngine
{

	namespace Importers
	{

		Texture* TextureImporter::LoadTexture(const char* path, bool sendMessage)
		{
            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, bpp;
            unsigned char* localBuffer = stbi_load(path, &width, &height, &bpp, 0);

            if (!localBuffer) 
            {
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

            if(sendMessage)
                std::cout << " Texture ID=" << textureID << " Successfully Loaded!\n";

            return new Texture(textureID, width, height, path);
		}

        unsigned int TextureImporter::TextureFromFile(const char* path, std::string& directory, bool gamma)
        {
            std::string filename = std::string(path);
            filename = directory + '/' + filename;

            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }

            return textureID;
        }

        void TextureImporter::Init(bool flip)
        {
            stbi_set_flip_vertically_on_load(flip);
        }

        

	}
}
