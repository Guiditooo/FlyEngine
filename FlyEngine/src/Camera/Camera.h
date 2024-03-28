#ifndef CAMERA_H
#define CAMERA_H

#include <Entity/Entity.h>

namespace FlyEngine
{

	class FLY_API Camera : public Entities::Entity
	{
	private:
		//glm::mat4 perspective;

	public:
		Camera();
		~Camera();

		void Draw() override;

	};
}

#endif // !CAMERA_H
