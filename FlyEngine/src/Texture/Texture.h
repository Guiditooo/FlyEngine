#ifndef TEXTURE_H
#define TEXTURE_H

#include <Exports/Exports.h>
#include <Window/Window.h>

namespace FlyEngine
{

	class Texture
	{
	private:
		unsigned int rendererID;
		std::string path;
		unsigned char* buffer;
		int width;
		int height;
		int bpp;
	public:
		Texture(const std::string& texturePath);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		int GetWidth();
		int GetHeight();
	};

}


#endif // !