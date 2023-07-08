#ifndef COLOR_H
#define COLOR_H

#include <FlyFunctions/ColorCode/ColorCode.h>
#include <glm/glm.hpp>

const int MAX_COLOR_SCALER = 256;

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
		Color(float r, float g, float b, float a);
		Color(float r, float g, float b);
		Color(int r, int g, int b, int a);
		Color(int r, int g, int b);
		Color(glm::vec4 rgba);
		Color(glm::vec3 rgb);
		Color(COLOR color);
		~Color();

		void SetColor(float r, float g, float b, float a);
		void SetColor(float r, float g, float b); 
		void SetColor(int r, int g, int b, int a);
		void SetColor(int r, int g, int b);
		void SetColor(glm::vec4 rgba);
		void SetColor(glm::vec3 rgb);
		void SetColor(Color color);
		void SetColor(COLOR color);
		
		Color GetColor();
		glm::vec4 GetColorV4();
		glm::vec3 GetColorV3();

		static glm::vec4 GetColorV4(COLOR color);
		static glm::vec3 GetColorV3(COLOR color);
		static Color* GetColor(COLOR color);
		static glm::vec4 GetRandomColor();
		
	};
}
#endif // !