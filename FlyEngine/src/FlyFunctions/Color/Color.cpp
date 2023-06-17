#include "Color.h"
#include <FlyFunctions/Commons/Commons.h>

FLY_ENGINE::Color::Color()
{
	red   = 1.0f;
	green = 1.0f;
	blue  = 1.0f;
	alpha = 1.0f;
}

FLY_ENGINE::Color::~Color()
{
}

void FLY_ENGINE::Color::SetColor(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void FLY_ENGINE::Color::SetColor(float r, float g, float b)
{
	red = r;
	green = g;
	blue = b;
	alpha = 1.0f;
}

void FLY_ENGINE::Color::SetColor(int r, int g, int b, int a)
{
	red = static_cast<float>(r) / 256;
	green = static_cast<float>(g) / 256;
	blue = static_cast<float>(b) / 256;
	alpha = static_cast<float>(a) / 256;
}

void FLY_ENGINE::Color::SetColor(int r, int g, int b)
{
	red = static_cast<float>(r) / 256;
	green = static_cast<float>(g) / 256;
	blue = static_cast<float>(b) / 256;
	alpha = 1.0f;
}

void FLY_ENGINE::Color::SetColor(glm::vec4 rgba)
{
	red = rgba.r;
	green = rgba.g;
	blue = rgba.b;
	alpha = rgba.a;
}

void FLY_ENGINE::Color::SetColor(glm::vec3 rgb)
{
	red = rgb.r;
	green = rgb.g;
	blue = rgb.b;
	alpha = 1.0f;
}

glm::vec4 FLY_ENGINE::Color::GetColor()
{
	return glm::vec4(red, green, blue, alpha);
}

glm::vec4 FLY_ENGINE::Color::GetColor(COLOR color)
{
	glm::vec4 newColor;
	newColor.a = 1.0f;

	switch (color)
	{
	case FLY_ENGINE::WHITE:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::RAYWHITE:
		newColor.r = 0.95f;
		newColor.g = 0.95f;
		newColor.b = 0.95f;
		break;
	case FLY_ENGINE::RED:
		newColor.r = 1.0f;
		newColor.g = 0.0f;
		newColor.b = 0.0f;
		break;
	case FLY_ENGINE::GREEN:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::BLUE:
		newColor.r = 0.0f;
		newColor.g = 0.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::MAGENTA:
		newColor.r = 1.0f;
		newColor.g = 0.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::YELLOW:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 0.0f;
		break;
	case FLY_ENGINE::CYAN:
		newColor.r = 0.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::BLACK:
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

glm::vec4 FLY_ENGINE::Color::GetRandomColor()
{
	float r = Commons::RandomFloat(0, 1);
	float g = Commons::RandomFloat(0, 1);
	float b = Commons::RandomFloat(0, 1);
	
	return glm::vec4(r, g, b, 1.0f);
}
