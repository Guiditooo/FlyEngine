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
			static Texture LoadTexture(const char* path);
		};

	}

}
#endif // !