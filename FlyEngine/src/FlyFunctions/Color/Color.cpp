#include "Color.h"
#include <FlyFunctions/Commons/Commons.h>

using namespace glm;

const int MAX_COLOR_SCALER = 256;

namespace FlyEngine
{

	namespace Utils
	{

		Color::Color()
		{
			red = 1.0f;
			green = 1.0f;
			blue = 1.0f;
			alpha = 1.0f;
		}

		Color::Color(float r, float g, float b, float a)
		{
			SetColor(r, g, b, a);
		}

		Color::Color(float r, float g, float b)
		{
			SetColor(r, g, b);
		}

		Color::Color(int r, int g, int b, int a)
		{
			SetColor(r, g, b, a);
		}

		Color::Color(int r, int g, int b)
		{
			SetColor(r, g, b);
		}

		Color::Color(glm::vec4 rgba)
		{
			SetColor(rgba);
		}

		Color::Color(glm::vec3 rgb)
		{
			SetColor(rgb);
		}

		Color::Color(COLOR color)
		{
			SetColor(color);
		}

		Color::~Color()
		{
		}

		void Color::SetColor(float r, float g, float b)
		{
			red = r;
			green = g;
			blue = b;
			alpha = 1.0f;
		}

		void Color::SetColor(float r, float g, float b, float a)
		{
			SetColor(r, g, b);
			alpha = a;
		}

		void Color::SetColor(int r, int g, int b)
		{
			if (red < 0) red = 0;
			if (red > MAX_COLOR_SCALER) red = MAX_COLOR_SCALER;
			red = static_cast<float>(r) / MAX_COLOR_SCALER;
			if (green < 0) green = 0;
			if (green > MAX_COLOR_SCALER) green = MAX_COLOR_SCALER;
			green = static_cast<float>(g) / MAX_COLOR_SCALER;
			if (blue < 0) blue = 0;
			if (blue > MAX_COLOR_SCALER) blue = MAX_COLOR_SCALER;
			blue = static_cast<float>(b) / MAX_COLOR_SCALER;
			alpha = 1.0f;
		}

		void Color::SetColor(int r, int g, int b, int a)
		{
			SetColor(r, g, b);
			if (alpha < 0) alpha = 0;
			if (alpha > MAX_COLOR_SCALER) alpha = MAX_COLOR_SCALER;
			alpha = static_cast<float>(a) / MAX_COLOR_SCALER;
		}


		void Color::SetColor(vec4 rgba)
		{
			red = rgba.r;
			green = rgba.g;
			blue = rgba.b;
			alpha = rgba.a;
		}

		void Color::SetColor(glm::vec3 rgb)
		{
			red = rgb.r;
			green = rgb.g;
			blue = rgb.b;
			alpha = 1.0f;
		}

		void Color::SetColor(Color color)
		{
			red = color.red;
			green = color.green;
			blue = color.blue;
			alpha = color.alpha;
		}

		void Color::SetColor(COLOR color)
		{
			SetColor(*GetColor(color));
		}

		Color Color::GetColor()
		{
			return Color(red, green, blue, alpha);
		}

		glm::vec4 Color::GetColorV4()
		{
			return glm::vec4(red, green, blue, alpha);
		}

		glm::vec3 Color::GetColorV3()
		{
			glm::vec3 color;
			color.r = red;
			color.g = green;
			color.b = blue;
			return color;
		}

		glm::vec4 Color::GetColorV4(COLOR color)
		{
			return glm::vec4(GetColorV3(color), 1.0f);
		}

		glm::vec3 Color::GetColorV3(COLOR color)
		{
			glm::vec3 newColor;

			switch (color)
			{
			case COLOR::WHITE:
				newColor.r = 1.0f;
				newColor.g = 1.0f;
				newColor.b = 1.0f;
				break;
			case COLOR::FLYWHITE:
				newColor.r = 0.92f;
				newColor.g = 0.92f;
				newColor.b = 0.92f;
				break;
			case COLOR::RED:
				newColor.r = 1.0f;
				newColor.g = 0.0f;
				newColor.b = 0.0f;
				break;
			case COLOR::GREEN:
				newColor.r = 0.0f;
				newColor.g = 1.0f;
				newColor.b = 0.0f;
				break;
			case COLOR::GREY:
				newColor.r = 0.5f;
				newColor.g = 0.5f;
				newColor.b = 0.5f;
				break;
			case COLOR::DARK_GREY:
				newColor.r = 0.2f;
				newColor.g = 0.2f;
				newColor.b = 0.2f;
				break;
			case COLOR::LIGHT_GREY:
				newColor.r = 0.8f;
				newColor.g = 0.8f;
				newColor.b = 0.8f;
				break;
			case COLOR::MOSS_GREEN:
				newColor.r = 0.2f;
				newColor.g = 0.3f;
				newColor.b = 0.3f;
				break;
			case COLOR::BLUE:
				newColor.r = 0.0f;
				newColor.g = 0.0f;
				newColor.b = 1.0f;
				break;
			case COLOR::MAGENTA:
				newColor.r = 1.0f;
				newColor.g = 0.0f;
				newColor.b = 1.0f;
				break;
			case COLOR::YELLOW:
				newColor.r = 1.0f;
				newColor.g = 1.0f;
				newColor.b = 0.0f;
				break;
			case COLOR::CYAN:
				newColor.r = 0.0f;
				newColor.g = 1.0f;
				newColor.b = 1.0f;
				break;
			case COLOR::FLYBLACK:
				newColor.r = 0.02f;
				newColor.g = 0.02f;
				newColor.b = 0.02f;
				break;
			case COLOR::BLACK:
				newColor.r = 0.0f;
				newColor.g = 0.0f;
				newColor.b = 0.0f;
				break;
			default:
				newColor.r = 1.0f;
				newColor.g = 1.0f;
				newColor.b = 1.0f;
				break;
			}

			return newColor;
		}

		Color* Color::GetColor(COLOR color)
		{
			return new Color(GetColorV4(color));
		}

		glm::vec4 Color::GetRandomColor()
		{
			float r = Commons::RandomFloat(0, 1);
			float g = Commons::RandomFloat(0, 1);
			float b = Commons::RandomFloat(0, 1);

			return glm::vec4(r, g, b, 1.0f);
		}

	}

}