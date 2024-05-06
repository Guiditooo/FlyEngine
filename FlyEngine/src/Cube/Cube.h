#ifndef CUBE_H
#define CUBE_H

#include <Entity3D/Entity3D.h>

namespace FlyEngine
{
	namespace Entities
	{

		class FLY_API Cube : public Entity3D
		{
		private:
		public:
			Cube();
			~Cube();
			void Draw() override;
		};

	}

}
#endif // !RECTANGLE_H