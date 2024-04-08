#ifndef COLORCODES_H
#define COLORCODES_H

#include <Exports/Exports.h>

namespace FlyEngine
{

	namespace Utils 
	{

		//#define COLOR_RED 1.0f, 0.0f, 0.0f, 1.0f
		//#define COLOR_FRANCE_BLUE 0.1f, 0.4f, 0.9f, 1.0f

		const int COLOR_COUNT = 10;

		enum class FLY_API COLOR
		{
			WHITE,
			RAYWHITE,
			RED,
			GREEN,
			BLUE,
			MAGENTA,
			YELLOW,
			CYAN,
			RAYBLACK,
			BLACK
		};

	}

}

#endif