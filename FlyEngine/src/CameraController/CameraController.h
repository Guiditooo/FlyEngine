#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Camera/Camera.h"

#include "Input/Input.h"

namespace FlyEngine
{
	using namespace Utils;

	struct FLY_API CameraRotation
	{
		float yaw;// = -90.0f; // Yaw inicial rot y
		float pitch;// = 0.0f; // Pitch inicial rot x
	};

	class FLY_API CameraController
	{
	private:
		Camera* camera;
		KeyCode forward;
		KeyCode backward;
		KeyCode up;
		KeyCode down;
		KeyCode left;
		KeyCode right;
		CameraRotation cameraRotation;
		float sensibility;
	public:
		CameraController(Camera* camera, Window* window, KeyCode forward, KeyCode backward, KeyCode up, KeyCode down, KeyCode left, KeyCode right);
		~CameraController();
		
		void SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetCamera(Camera* newCamera);

		Camera* GetCamera();

		void Update();
	};
}
#endif // 