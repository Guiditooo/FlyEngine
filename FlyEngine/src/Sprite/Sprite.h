#ifndef SPRITE_H
#define SPRITE_H

#include <Entity2D/Entity2D.h>

namespace FlyEngine
{
	namespace Entities
	{
		struct SpriteDims
		{
			int width;
			int height;
		};

		class FLY_API Sprite : public Entity2D
		{
		private:
			static int internalID;
			std::string textureCode;
			int texture;
			int width;
			int height;

		public:
			Sprite(const char* path, bool creationMessage = false);
			~Sprite();

			SpriteDims GetDimentions();
			int GetTexture();

			void SetSpriteDims(SpriteDims dims);

		};

	}

}
#endif // !SPRITE_H