#ifndef COMMONS_H
#define COMMONS_H

#include <Exports/Exports.h>
#include <Window/Window.h>

namespace FlyEngine
{

	namespace Utils
	{

		class FLY_API Commons
		{
		private:
		public:
			static float RandomFloat(float initRange, float endRange);
		};

	}

}
#endif // !