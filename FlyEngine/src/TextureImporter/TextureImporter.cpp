#include "TextureImporter.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#include "TextureManager/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const std::vector<std::string> supportedExtensions = { ".png", ".jpg", ".jpeg", ".bmp", ".tga" };

using namespace std::filesystem;

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

			if (sendMessage)
				std::cout << " Texture ID=" << textureID << " Successfully Loaded!";

			return new Texture(textureID, width, height, path);
		}

		Texture* TextureImporter::SearchTexture(std::string directory, std::string filename, bool sendMessage)
		{
			try
			{
				//std::cout << "Searching in directory: " << directory << std::endl;
				for (const auto& entry : std::filesystem::directory_iterator(directory))
				{
					if (entry.is_regular_file())
					{
						std::string extension = entry.path().extension().string();
						std::string name = entry.path().stem().string(); // Get the filename without extension
						if (name == filename && std::find(supportedExtensions.begin(), supportedExtensions.end(), extension) != supportedExtensions.end())
						{
							return LoadTexture(entry.path().string().c_str(), true);
						}
					}
				}
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				std::cerr << "Filesystem error: " << e.what() << std::endl;
				return Managers::TextureManager::GetDefaultTexture();
			}
			std::cerr << "Texture not found: " << directory << "/" << filename << std::endl;
			return Managers::TextureManager::GetDefaultTexture();
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
