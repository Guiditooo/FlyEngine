#include <string>

#include "CameraController.h"
#include "FlyFunctions/Debugger/Debugger.h"

//FlyEngine::CameraController* newCamera;
bool isFirstTime = true;
static double lastMouseX;
static double  lastMouseY;


namespace FlyEngine
{
	CameraController* CameraController::instance = nullptr;

	Camera* CameraController::camera = nullptr;
	CameraRotation CameraController::cameraRotation = {};
	float CameraController::rotationSensitivity = 0.1f;
	float CameraController::translateSensitivity = 0.1f;

	CameraMode CameraController::cameraMode = CameraMode::Free;

	float CameraController::lastX = 0.0f;
	float CameraController::lastY = 0.0f;

	ObjetiveParams* CameraController::objetiveParams = nullptr;
	bool CameraController::isMouseMovementOn = false;

	glm::vec3 CameraController::previousRot = glm::vec3(0);

	Utils::Input innerSystemInput;

	CameraController::CameraController() {}

	CameraController::~CameraController() {}

	void CameraController::SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		camera->SetProjectionType(projType);
		camera->SetFoV(fov);
		camera->SetAspectRatio(aspectRatio);
		camera->SetPlanes(nearPlane, farPlane);
	}

	void CameraController::SetCamera(Camera* newCamera)
	{
		camera = newCamera;
	}

	void CameraController::SetObjetiveParameters(ObjetiveParams* newObjParams)
	{
		objetiveParams = newObjParams;
	}

	void CameraController::SetMode(CameraMode mode)
	{
		cameraMode = mode;
	}

	void CameraController::SetFirstTarget(Entities::Entity* target)
	{
		cameraMode = CameraMode::FirstPerson;
		objetiveParams->target = target;
		glm::vec3 targetPos = target->GetTransform()->GetWorldPosition();
		camera->GetTransform()->SetWorldPosition(targetPos.x, targetPos.y, targetPos.z);
		glm::vec3 targetRot = target->GetTransform()->GetFront();
		camera->GetTransform()->SetWorldRotation(targetRot.x, targetRot.y, targetRot.z);
	}
	void CameraController::SetThirdTarget(Entities::Entity* target, float distance)
	{
		cameraMode = CameraMode::ThirdPerson;
		objetiveParams->target = target;
		//glm::vec3 targetPos = target->GetPosition() + camera->GetFront() * distance;
		glm::vec3 targetPos = camera->GetTransform()->GetWorldPosition();
		camera->GetTransform()->SetWorldPosition(targetPos.x, targetPos.y + 2, targetPos.z - 5);

	}

	Entities::Entity* CameraController::GetTarget()
	{
		return objetiveParams->target;
	}

	CameraController* CameraController::Initialize(Camera* newCamera, Window* window)
	{
		camera = newCamera;

		rotationSensitivity = 0.3f;
		translateSensitivity = 0.05f;

		previousRot = glm::vec3(0);

		cameraRotation = CameraRotation();

		cameraMode = CameraMode::Free;

		objetiveParams = new ObjetiveParams(nullptr, 0.0f);

		isMouseMovementOn = false;

		lastX = 0;
		lastY = 0;


		return GetInstance();
	}

	void CameraController::SetDistanceToTarget(float distanceToTarget)
	{
		objetiveParams->distanceFromObjetive = distanceToTarget;
	}

	Camera* CameraController::GetCamera()
	{
		return camera;
	}

	void CameraController::Update(bool showMessage)
	{
		bool cameraMoved = false;

		switch (cameraMode)
		{
		case CameraMode::FirstPerson:
			FirstPersonMovement(cameraMoved);
			break;
		case CameraMode::ThirdPerson:
			ThirdPersonMovement(cameraMoved);
			break;
		case CameraMode::Free:
			FreeMovement(cameraMoved);
			break;
		default:
			break;
		}

		if (showMessage)
		{
			Debugger::ConsoleMessage("- Camera Updated Front :", camera->GetTransform()->GetFront());
			if (cameraMoved)
				Debugger::ConsoleMessage("- Camera Updated Position :", camera->GetTransform()->GetWorldPosition());
		}
	}

	void CameraController::ProcessMouseMovement(float xOffset, float yOffset)
	{
		if (!isMouseMovementOn)
			return;

		float sensitivity = 0.1f;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		cameraRotation.yaw += xOffset;
		cameraRotation.pitch -= yOffset;

		if (cameraRotation.pitch > 89.0f)
			cameraRotation.pitch = 89.0f;
		if (cameraRotation.pitch < -89.0f)
			cameraRotation.pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
		front.y = sin(glm::radians(cameraRotation.pitch));
		front.z = sin(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
		front = glm::normalize(front);

		camera->GetTransform()->SetFront(front);
		//camera->GetTransform()->LocalRotateAround(cameraRotation.pitch, -cameraRotation.yaw, 0);
		//camera->GetTransform()->WorldRotateAround(cameraRotation.pitch, -cameraRotation.yaw, 0);

		Debugger::ConsoleMessage("Camera Front:", front);

		camera->viewMatrix = glm::lookAt(
			camera->GetTransform()->GetLocalPosition(),
			camera->GetTransform()->GetLocalPosition() + front,
			camera->GetTransform()->GetUp()
		);
	}

	void CameraController::FreeMovement(bool& cameraMoved)
	{

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
		{
			camera->MoveForward(translateSensitivity);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_S))
		{
			camera->MoveBackward(translateSensitivity);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_SPACE))
		{
			camera->MoveUp(translateSensitivity);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			camera->MoveDown(translateSensitivity);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_A))
		{
			camera->MoveLeft(translateSensitivity);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_D))
		{
			camera->MoveRight(translateSensitivity);
			cameraMoved = true;
		}
		
		camera->viewMatrix = glm::lookAt(
			camera->GetTransform()->GetLocalPosition(), 
			camera->GetTransform()->GetLocalPosition() + camera->GetTransform()->GetFront(), 
			camera->GetTransform()->GetUp());
		
	}

	void CameraController::FirstPersonMovement(bool& cameraMoved)
	{
		/*
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT))
		{
			camera->WorldRotate(0.0f, rotationSensitivity, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_RIGHT))
		{
			camera->WorldRotate(0.0f, -rotationSensitivity, 0.0f);
			cameraMoved = true;
		}

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_UP))
		{
			camera->WorldRotate(-rotationSensitivity, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_DOWN))
		{
			camera->WorldRotate(rotationSensitivity, 0.0f, 0.0f);
			cameraMoved = true;
		}
		*/
		if (objetiveParams->target != nullptr)
		{
			glm::vec3 objPos = objetiveParams->target->GetTransform()->GetWorldPosition();
			camera->GetTransform()->SetWorldPosition(objPos.x, objPos.y, objPos.z);
			glm::vec3 objRot = objetiveParams->target->GetTransform()->GetFront();
			camera->GetTransform()->SetWorldRotation(objRot.x, objRot.y, objRot.z);
		}
		else
		{
			Debugger::ConsoleMessage("ERROR - CAMERA CONTROLLER HAS NOT TARGET");
		}

		
		camera->viewMatrix = glm::lookAt(
			camera->GetTransform()->GetWorldPosition(), 
			camera->GetTransform()->GetWorldPosition() + camera->GetTransform()->GetFront(), 
			camera->GetTransform()->GetUp());
		

	}

	void CameraController::ThirdPersonMovement(bool& cameraMoved)
	{

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_ADD))
		{
			float coef = 1.01f;
			objetiveParams->distanceFromObjetive *= coef;
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_SUBTRACT))
		{
			float coef = 0.99f;
			objetiveParams->distanceFromObjetive *= coef;
			cameraMoved = true;
		}

		if (objetiveParams->target != nullptr)
		{
			/*glm::vec3 targetPosition = objetiveParams->target->GetPosition();
			float distanceToTarget = objetiveParams->distanceFromObjetive;

			float cameraX = targetPosition.x + distanceToTarget * cos(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
			float cameraY = targetPosition.y + distanceToTarget * sin(glm::radians(cameraRotation.pitch));
			float cameraZ = targetPosition.z + distanceToTarget * sin(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
			*/

			
			camera->viewMatrix = glm::lookAt(camera->GetTransform()->GetWorldPosition(), objetiveParams->target->GetTransform()->GetWorldPosition(), camera->GetTransform()->GetUp());
			


			glm::vec3 targetPos = objetiveParams->target->GetTransform()->GetWorldPosition() + camera->GetTransform()->GetFront() * 5.0f;
			camera->GetTransform()->SetWorldPosition(targetPos.x, targetPos.y, targetPos.z);

			float rotY = previousRot.y - objetiveParams->target->GetTransform()->GetWorldRotation().y;
			cameraRotation.yaw += glm::degrees(rotY);

			camera->GetTransform()->WorldRotateAround(cameraRotation.pitch, -cameraRotation.yaw, 0);

			previousRot = objetiveParams->target->GetTransform()->GetWorldRotation();

		}

	}

	void CameraController::SetMouseMovementOn(bool value)
	{
		isMouseMovementOn = value;
	}
	bool CameraController::IsMouseMovementOn()
	{
		return isMouseMovementOn;
	}

	CameraController* CameraController::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CameraController(); // Se crea la instancia si no existe
		}
		return instance;
	}

	void CameraController::DestroyInstance()
	{
		if (objetiveParams != nullptr)
			delete objetiveParams;
		objetiveParams = nullptr;

		if (instance != nullptr)
			delete instance;
		instance = nullptr;
	}


	void CameraController::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (isFirstTime)
		{
			lastMouseX = xpos;
			lastMouseY = ypos;
			isFirstTime = false;
		}

		float xOffset = xpos - lastMouseX;
		float  yOffset = lastMouseY - ypos;

		lastMouseX = xpos;
		lastMouseY = ypos;

		FlyEngine::CameraController::GetInstance()->ProcessMouseMovement(xOffset, yOffset);
	}

}
