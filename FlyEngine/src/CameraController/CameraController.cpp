#include <string>

#include "CameraController.h"
#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{

	Utils::Input innerSystemInput;

	CameraController::CameraController(Camera* camera, Window* window)
	{
		this->camera = camera;

		rotationSensitivity = 0.3f;
		translateSensitivity = 0.05f;

		cameraRotation = CameraRotation();

		cameraMode = CameraMode::Free;

		objetiveParams = new ObjetiveParams(nullptr, 0.0f);
	}

	CameraController::~CameraController()
	{
		if (camera != nullptr)
			delete camera;
		camera = nullptr;
	}

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
		glm::vec3 targetPos = target->GetTransform()->GetPosition();
		camera->SetPosition(targetPos.x, targetPos.y, targetPos.z);
		glm::vec3 targetRot = target->GetTransform()->GetFront();
		camera->SetRotation(targetRot.x, targetRot.y, targetRot.z);
	}
	void CameraController::SetThirdTarget(Entities::Entity* target, float distance)
	{
		cameraMode = CameraMode::ThirdPerson;
		objetiveParams->target = target;
		//glm::vec3 targetPos = target->GetPosition() + camera->GetFront() * distance;
		glm::vec3 targetPos = camera->GetTransform()->GetPosition();
		camera->SetPosition(targetPos.x, targetPos.y+2, targetPos.z-5);

	}

	Entities::Entity* CameraController::GetTarget()
	{
		return objetiveParams->target;
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

		if (showMessage && cameraMoved)
		{
			/*
			std::string text = "- Camera Updated Position: (";
			text += std::to_string(camera->GetPosition().x);
			text += ",";
			text += std::to_string(camera->GetPosition().y);
			text += ",";
			text += std::to_string(camera->GetPosition().z);
			text += ")";
			Debugger::ConsoleMessage(&text[0], 1, 0, 1, 0);
			*/
		}
	}

	void CameraController::ProcessMouseMovement(float xOffset, float yOffset)
	{
		if (!isMouseMovementOn)
			return;
		
		//El mouse se mueve
		float sensitivity = 0.1f;

		xOffset *= sensitivity;
		yOffset *= sensitivity;

		cameraRotation.yaw += xOffset;
		cameraRotation.pitch += yOffset;

		if (cameraRotation.pitch > 89.0f)
			cameraRotation.pitch = 89.0f;
		if (cameraRotation.pitch < -89.0f)
			cameraRotation.pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
		front.y = sin(glm::radians(cameraRotation.pitch));
		front.z = sin(glm::radians(cameraRotation.yaw)) * cos(glm::radians(cameraRotation.pitch));
		//camera->SetFront(glm::normalize(front));

		camera->GetTransform()->RotateAround(cameraRotation.pitch, -cameraRotation.yaw, 0);
		/*
		std::string text = "- ";
		text += camera->GetName();
		text += " Updated Rot: ";
		Debugger::ConsoleMessage(&text[0], camera->GetRotation());
		*/
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

		camera->viewMatrix = glm::lookAt(camera->GetTransform()->GetPosition(), camera->GetTransform()->GetPosition() + camera->GetTransform()->GetFront(), camera->GetTransform()->GetUp());

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
			glm::vec3 objPos = objetiveParams->target->GetTransform()->GetPosition();
			camera->SetPosition(objPos.x, objPos.y, objPos.z);
			glm::vec3 objRot = objetiveParams->target->GetTransform()->GetFront();
			camera->SetRotation(objRot.x, objRot.y, objRot.z);
		}
		else
		{
			Debugger::ConsoleMessage("ERROR - CAMERA CONTROLLER HAS NOT TARGET");
		}

		camera->viewMatrix = glm::lookAt(camera->GetTransform()->GetPosition(), camera->GetTransform()->GetPosition() + camera->GetTransform()->GetFront(), camera->GetTransform()->GetUp());
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
			camera->viewMatrix = glm::lookAt(camera->GetTransform()->GetPosition(), objetiveParams->target->GetTransform()->GetPosition(), camera->GetTransform()->GetUp());

			glm::vec3 targetPos = objetiveParams->target->GetTransform()->GetPosition() + camera->GetTransform()->GetFront() * 5.0f;
			camera->SetPosition(targetPos.x, targetPos.y, targetPos.z);

			float rotY = previousRot.y - objetiveParams->target->GetTransform()->GetRotation().y;
			cameraRotation.yaw += glm::degrees(rotY);

			camera->GetTransform()->RotateAround(cameraRotation.pitch, -cameraRotation.yaw, 0);
			
			previousRot = objetiveParams->target->GetTransform()->GetRotation();

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

}