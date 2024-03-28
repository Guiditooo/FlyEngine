#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Shape/Shape.h>

namespace FlyEngine
{

	namespace Entities
	{

		class FLY_API Triangle : public Shape
		{
		private:
		public:
			Triangle();
			~Triangle();
			void Draw() override;
		};

	}
}

#endif // !TRIANGLE_H