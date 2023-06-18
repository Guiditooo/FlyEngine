#include "Color.h"
#include <FlyFunctions/Commons/Commons.h>

using namespace glm;

FLY_ENGINE::Color::Color()
{
	red   = 1.0f;
	green = 1.0f;
	blue  = 1.0f;
	alpha = 1.0f;
}

FLY_ENGINE::Color::Color(float r, float g, float b, float a)
{
	SetColor(r, g, b, a);
}

FLY_ENGINE::Color::Color(float r, float g, float b)
{
	SetColor(r, g, b);
}

FLY_ENGINE::Color::Color(int r, int g, int b, int a)
{
	SetColor(r, g, b, a);
}

FLY_ENGINE::Color::Color(int r, int g, int b)
{
	SetColor(r, g, b);
}

FLY_ENGINE::Color::Color(glm::vec4 rgba)
{
	SetColor(rgba);
}

FLY_ENGINE::Color::Color(glm::vec3 rgb)
{
	SetColor(rgb);
}

FLY_ENGINE::Color::Color(COLOR color)
{
	SetColor(color);
}

FLY_ENGINE::Color::~Color()
{
}

void FLY_ENGINE::Color::SetColor(float r, float g, float b)
{
	red = r;
	green = g;
	blue = b;
	alpha = 1.0f;
}

void FLY_ENGINE::Color::SetColor(float r, float g, float b, float a)
{
	SetColor(r, g, b);
	alpha = a;
}

void FLY_ENGINE::Color::SetColor(int r, int g, int b)
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

void FLY_ENGINE::Color::SetColor(int r, int g, int b, int a)
{
	SetColor(r, g, b);
	if (alpha < 0) alpha = 0;
	if (alpha > MAX_COLOR_SCALER) alpha = MAX_COLOR_SCALER;
	alpha = static_cast<float>(a) / MAX_COLOR_SCALER;
}


void FLY_ENGINE::Color::SetColor(vec4 rgba)
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

void FLY_ENGINE::Color::SetColor(Color color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
	alpha = color.alpha;
}

void FLY_ENGINE::Color::SetColor(COLOR color)
{
	SetColor(*GetColor(color));
}

glm::vec4 FLY_ENGINE::Color::GetColor()
{
	return glm::vec4(red, green, blue, alpha);
}

glm::vec4 FLY_ENGINE::Color::GetColorV4(COLOR color)
{
	glm::vec4 newColor;
	newColor.a = 1.0f;

	switch (color)
	{
	case FLY_ENGINE::COLOR::WHITE:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::COLOR::RAYWHITE:
		newColor.r = 0.92f;
		newColor.g = 0.92f;
		newColor.b = 0.92f;
		break;
	case FLY_ENGINE::COLOR::RED:
		newColor.r = 1.0f;
		newColor.g = 0.0f;
		newColor.b = 0.0f;
		break;
	case FLY_ENGINE::COLOR::GREEN:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::COLOR::BLUE:
		newColor.r = 0.0f;
		newColor.g = 0.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::COLOR::MAGENTA:
		newColor.r = 1.0f;
		newColor.g = 0.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::COLOR::YELLOW:
		newColor.r = 1.0f;
		newColor.g = 1.0f;
		newColor.b = 0.0f;
		break;
	case FLY_ENGINE::COLOR::CYAN:
		newColor.r = 0.0f;
		newColor.g = 1.0f;
		newColor.b = 1.0f;
		break;
	case FLY_ENGINE::COLOR::BLACK:
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

FLY_ENGINE::Color* FLY_ENGINE::Color::GetColor(COLOR color)
{
	return new Color(GetColorV4(color));
}

glm::vec4 FLY_ENGINE::Color::GetRandomColor()
{
	float r = Commons::RandomFloat(0, 1);
	float g = Commons::RandomFloat(0, 1);
	float b = Commons::RandomFloat(0, 1);
	
	return glm::vec4(r, g, b, 1.0f);
}
