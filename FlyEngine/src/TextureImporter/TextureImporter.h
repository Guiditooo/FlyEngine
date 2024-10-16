#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "Exports/Exports.h"
#include "Texture/Texture.h"

namespace FlyEngine
{
	namespace Importers
	{
		class FLY_API TextureImporter
		{
		private:
		public:
			static Texture* LoadTexture(const char* path, bool sendMessage);
			static Texture* SearchTexture(const std::string& directory, const std::string& filename);
			static unsigned int TextureFromFile(const char* path, std::string& directory, bool gamma = false);
			static void Init(bool flip);
		};

	}

}
#endif // !TEXTURE_IMPORTER_H