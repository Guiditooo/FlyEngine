#ifndef LIGHT_TYPE_H
#define LIGHT_TYPE_H

#include <Exports/Exports.h>

namespace FlyEngine
{

	namespace Lights
	{

		enum class FLY_API LightType
		{
			Directional,
			Point,
			Spot
		};

	}
}

#endif // !LIGHT_TYPE_H