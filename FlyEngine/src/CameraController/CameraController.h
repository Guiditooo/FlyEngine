#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <functional>

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
		float yaw = 0.0f;
		float pitch = 0.0f;
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
		static Camera* camera;
		static CameraRotation cameraRotation;
		static float rotationSensitivity ;
		static float translateSensitivity;

		static CameraMode cameraMode;

		static float lastX;
		static float lastY;

		static ObjetiveParams* objetiveParams;

		static bool isMouseMovementOn;

		static glm::vec3 previousRot;

		void FreeMovement(bool &cameraMoved);
		void FirstPersonMovement(bool &cameraMoved);
		void ThirdPersonMovement(bool &cameraMoved);

		CameraController();
		~CameraController();

		static CameraController* instance;

	public:
		CameraController(const CameraController&) = delete;
		CameraController& operator=(const CameraController&) = delete;

		static  CameraController* Initialize(Camera* newCamera, Window* window);
		static CameraController* GetInstance();
		static void DestroyInstance();
		
		void SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetCamera(Camera* newCamera);
		void SetObjetiveParameters(ObjetiveParams* newObjParams);
		void SetMode(CameraMode mode);
		void SetFirstTarget(Entities::Entity* target);
		void SetThirdTarget(Entities::Entity* target, float distance);
		void SetDistanceToTarget(float distanceToTarget);


		Entities::Entity* GetTarget();

		void SetMouseMovementOn(bool value);
		bool IsMouseMovementOn();

		Camera* GetCamera();

		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		void Update(bool showMessage);   
		void ProcessMouseMovement(float xOffset, float yOffset);

	};
}
#endif // 