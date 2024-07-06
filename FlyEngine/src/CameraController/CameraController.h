#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Camera/Camera.h"

#include "Input/Input.h"

namespace FlyEngine
{
	using namespace Utils;

	enum class FLY_API CameraMode
	{
		FirstPerson,
		ThirdPerson,
		Free
	};

	struct FLY_API CameraRotation
	{
		float yaw;// = -90.0f; // Yaw inicial rot y
		float pitch;// = 0.0f; // Pitch inicial rot x
	};

	struct FLY_API ObjetiveParams
	{
		Entities::Entity* target;
		float distanceFromObjetive;
		
		ObjetiveParams(Entities::Entity* newObjetive, float distance)
		{
			target = newObjetive;
			distanceFromObjetive = distance;
		}
	};

	class FLY_API CameraController
	{
	private:
		Camera* camera;
		CameraRotation cameraRotation;
		float rotationSensibility;
		float translateSensibility;

		CameraMode cameraMode;

		float lastX;
		float lastY;

		ObjetiveParams* objetiveParams;

		void FreeMovement(bool &cameraMoved);
		void FirstPersonMovement(bool &cameraMoved);
		void ThirdPersonMovement(bool &cameraMoved);

	public:
		CameraController(Camera* camera, Window* window);
		~CameraController();
		
		void SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetCamera(Camera* newCamera);
		void SetObjetiveParameters(ObjetiveParams* newObjParams);
		void SetMode(CameraMode mode);
		void SetTarget(Entities::Entity* target);
		void SetDistanceToTarget(float distanceToTarget);

		Camera* GetCamera();

		void Update(bool showMessage);   
		void ProcessMouseMovement(float xpos, float ypos);
	};
}
#endif // 