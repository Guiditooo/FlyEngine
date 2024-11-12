#ifndef TEXTURE_H
#define TEXTURE_H

#include <Exports/Exports.h>
#include <Window/Window.h>

namespace FlyEngine
{

	class FLY_API Texture
	{
	private:
		unsigned int id;
		std::string path;
		std::string type;
		int width;
		int height;

		bool isActive;
	public:
		Texture(unsigned int id, int textureWidth, int textureHeight, const std::string& texturePath);
		~Texture();

		//void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		void SetType(std::string type);

		unsigned int GetID() const;
		const std::string& GetPath();
		int GetWidth();
		int GetHeight();
		bool IsActive();
	};

}


#endif // !