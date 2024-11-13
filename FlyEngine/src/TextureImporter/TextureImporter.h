#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include <iostream>

#include "Exports/Exports.h"

namespace FlyEngine
{
	class Texture;
	
	namespace Importers
	{

		class FLY_API TextureImporter
		{
		private:
		public:
			static Texture* LoadTexture(const char* path, bool sendMessage = true);
			static Texture* SearchTexture(std::string directory, std::string filename, bool sendMessage = true);
			static unsigned int TextureFromFile(const char* path, std::string& directory, bool gamma = false);
			static void Init(bool flip);
		};

	}

}
#endif // !TEXTURE_IMPORTER_H