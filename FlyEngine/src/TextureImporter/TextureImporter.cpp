#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace FlyEngine
{
	namespace Importers
	{

		Texture TextureImporter::LoadTexture(const char* path)
		{
            int width, height, bpp;
            stbi_set_flip_vertically_on_load(1);
            unsigned char* localBuffer = stbi_load(path, &width, &height, &bpp, 4);

            if (!localBuffer) {
                std::cerr << "Error loading texture: " << path << std::endl;
                return Texture(0, 0, 0, "");
            }

            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(localBuffer);

            return Texture(textureID, width, height, path);
		}

	}
}
