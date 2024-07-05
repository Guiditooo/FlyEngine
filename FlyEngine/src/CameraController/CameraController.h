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

	struct FLY_API ObjetiveParams
	{
		Entities::Entity* objetive;
		float distanceFromObjetive;
		
		ObjetiveParams(Entities::Entity* newObjetive, float distance)
		{
			objetive = newObjetive;
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

		bool isFirst;

		ObjetiveParams* objetiveParams;
	public:
		CameraController(Camera* camera, Window* window);
		~CameraController();
		
		void SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetCamera(Camera* newCamera);
		void SetObjetiveParameters(ObjetiveParams* newObjParams);

		Camera* GetCamera();

		void Update(bool showMessage);
	};
}
#endif // 