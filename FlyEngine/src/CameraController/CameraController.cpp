#include <string>

#include "CameraController.h"
#include "FlyFunctions/Debugger/Debugger.h"

FlyEngine::Utils::Input innerSystemInput;

FlyEngine::CameraController::CameraController(Camera* camera, Window* window)
{
	this->camera = camera;

	rotationSensibility = 0.3f;
	translateSensibility = 0.05f;

	cameraRotation = CameraRotation();

	cameraMode = CameraMode::Free;

	objetiveParams = new ObjetiveParams(nullptr, 0.0f);
}

FlyEngine::CameraController::~CameraController()
{
	if (camera != nullptr)
		delete camera;
	camera = nullptr;
}

void FlyEngine::CameraController::SetCameraSpecs(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane)
{
	camera->SetProjectionType(projType);
	camera->SetFoV(fov);
	camera->SetAspectRatio(aspectRatio);
	camera->SetPlanes(nearPlane, farPlane);
}

void FlyEngine::CameraController::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}

void FlyEngine::CameraController::SetObjetiveParameters(ObjetiveParams* newObjParams)
{
	objetiveParams = newObjParams;
}

void FlyEngine::CameraController::SetMode(CameraMode mode)
{
	cameraMode = mode;
}

void FlyEngine::CameraController::SetTarget(Entities::Entity* target)
{
	objetiveParams->target = target;
}

void FlyEngine::CameraController::SetDistanceToTarget(float distanceToTarget)
{
	objetiveParams->distanceFromObjetive = distanceToTarget;
}

FlyEngine::Camera* FlyEngine::CameraController::GetCamera()
{
	return camera;
}

void FlyEngine::CameraController::Update(bool showMessage)
{
	bool cameraMoved = false;

	switch (cameraMode)
	{
	case FlyEngine::CameraMode::FirstPerson:
		FirstPersonMovement(cameraMoved);
		break;
	case FlyEngine::CameraMode::ThirdPerson:
		ThirdPersonMovement(cameraMoved);
		break;
	case FlyEngine::CameraMode::Free:
		FreeMovement(cameraMoved);
		break;
	default:
		break;
	}

	if (showMessage && cameraMoved)
	{
		std::string text = "- Camera Updated Position: (";
		text += std::to_string(camera->GetPosition().x);
		text += ",";
		text += std::to_string(camera->GetPosition().y);
		text += ",";
		text += std::to_string(camera->GetPosition().z);
		text += ")";
		Debugger::ConsoleMessage(&text[0], 1, 0, 1, 0);
	}
}

void FlyEngine::CameraController::ProcessMouseMovement(float xpos, float ypos)
{
	lastX = xpos;
	lastY = ypos;

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos; // Invertido porque y-coordinates van de abajo hacia arriba
	lastX = xpos;
	lastY = ypos;

	xOffset *= rotationSensibility;
	yOffset *= rotationSensibility;

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
}

void FlyEngine::CameraController::FreeMovement(bool &cameraMoved)
{
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
	{
		camera->MoveForward(translateSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_S))
	{
		camera->MoveBackward(translateSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_SPACE))
	{
		camera->MoveUp(translateSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT_SHIFT))
	{
		camera->MoveDown(translateSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_A))
	{
		camera->MoveLeft(translateSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_D))
	{
		camera->MoveRight(translateSensibility);
		cameraMoved = true;
	}

	if (Input::GetKeyPressed(Utils::KeyCode::KEY_I))
	{
		camera->Rotate(rotationSensibility, 0.0f, 0.0f);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_K))
	{
		camera->Rotate(-rotationSensibility, 0.0f, 0.0f);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_J))
	{
		camera->Rotate(0.0f, rotationSensibility, 0.0f);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_L))
	{
		camera->Rotate(0.0f, -rotationSensibility, 0.0f);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_U))
	{
		camera->Rotate(0.0f, 0.0f, rotationSensibility);
		cameraMoved = true;
	}
	if (Input::GetKeyPressed(Utils::KeyCode::KEY_O))
	{
		camera->Rotate(0.0f, 0.0f, -rotationSensibility);
		cameraMoved = true;
	}

}

void FlyEngine::CameraController::FirstPersonMovement(bool& cameraMoved)
{
}

void FlyEngine::CameraController::ThirdPersonMovement(bool& cameraMoved)
{
}