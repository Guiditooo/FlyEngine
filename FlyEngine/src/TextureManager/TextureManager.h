#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <iostream>
#include <unordered_map>

#include "Texture/Texture.h"

namespace FlyEngine
{
	namespace Managers
	{
		class FLY_API TextureManager
		{
		private:
			static std::unordered_map<std::string, Texture*> textureMap; //Tambien probar con los IDs

			static void CreateDefaultTexture();

		public:
			static void InitializeManager();
			static int CreateTexture(std::string textureName, const char* path);
			static int CreateSearchedTexture(std::string directory, std::string filename, std::string textureName, bool sendMessage = true);

			static int GetTextureID(std::string textureName);
			static int GetDefaultTextureID();

			static Texture* GetDefaultTexture();
			static Texture* GetTexture(std::string textureName);

			static void SetTextureType(int textureID, std::string type);

			static void BindTexture(int textureID, unsigned int slot = 0);
			static void UnBindTexture();
		};
	}
}

#endif // !TEXTURE_MANAGER_H
