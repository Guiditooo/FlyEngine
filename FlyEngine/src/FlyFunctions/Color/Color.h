#ifndef COLOR_H
#define COLOR_H

#include <FlyFunctions/ColorCode/ColorCode.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace FLY_ENGINE
{
	class FLY_API Color
	{
	private:
		float red;
		float green;
		float blue;
		float alpha;
	public:
		Color();
		~Color();

		void SetColor(float r, float g, float b, float a);
		void SetColor(float r, float g, float b); 
		void SetColor(int r, int g, int b, int a);
		void SetColor(int r, int g, int b);
		void SetColor(glm::vec4 rgba);
		void SetColor(glm::vec3 rgb);
		glm::vec4 GetColor();

		static glm::vec4 GetColor(COLOR color);
		static glm::vec4 GetRandomColor();
		
	};
}
#endif // !