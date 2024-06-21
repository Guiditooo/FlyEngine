#ifndef SHAPE_H
#define SHAPE_H

#include <Entity2D/Entity2D.h>

namespace FlyEngine
{

	namespace Entities
	{

		class Shape : public Entity2D
		{
		private:

		public:
			Shape(std::string name);
		};

	}

}

#endif // !SHAPE_H