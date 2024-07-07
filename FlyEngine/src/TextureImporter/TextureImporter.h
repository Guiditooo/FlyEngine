#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "Exports/Exports.h"
#include "Texture/Texture.h"

namespace FlyEngine
{
	namespace Entities
	{
		struct Texture;
	}

	namespace Importers
	{

		class FLY_API TextureImporter
		{
		private:
		public:
			static Texture* LoadTexture(const char* path, bool sendMessage);
			static unsigned int TextureFromFile(const char* path, std::string& directory, bool gamma = false);
		};

	}

}
#endif // !TEXTURE_IMPORTER_H