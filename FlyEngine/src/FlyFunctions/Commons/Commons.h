#ifndef COMMONS_H
#define COMMONS_H

#include <Exports/Exports.h>
#include <GLFW/glfw3.h>

namespace FLY_ENGINE
{

	class FLY_API Commons
	{
	private:

	public:
		static float RandomFloat(float initRange, float endRange);
	};
}
#endif // !