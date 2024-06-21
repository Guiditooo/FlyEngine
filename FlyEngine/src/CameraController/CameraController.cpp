#include <string>

#include "CameraController.h"
#include "FlyFunctions/Debugger/Debugger.h"

FlyEngine::Utils::Input innerSystemInput;

FlyEngine::CameraController::CameraController(Camera* camera, Window* window, KeyCode forward, KeyCode backward, KeyCode up, KeyCode down, KeyCode left, KeyCode right)
{
	this->camera = camera;
	
	this->forward = forward;
	this->backward = backward;
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;

	sensibility = 0.01f;

	innerSystemInput = FlyEngine::Utils::Input(window);

	cameraRotation = CameraRotation();
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

FlyEngine::Camera* FlyEngine::CameraController::GetCamera()
{
	return camera;
}

void FlyEngine::CameraController::Update()
{
	bool cameraMoved = false;

	if (innerSystemInput.GetKeyDown(forward))
	{
		camera->Translate(0.0f, 0.0f, sensibility);
		cameraMoved = true;
	}
	if (innerSystemInput.GetKeyDown(backward))
	{
		camera->Translate(0.0f, 0.0f, -sensibility);
		cameraMoved = true;
	}
	if (innerSystemInput.GetKeyDown(up))
	{
		camera->Translate(0.0f, -sensibility, 0.0f);
		cameraMoved = true;
	}
	if (innerSystemInput.GetKeyDown(down))
	{
		camera->Translate(0.0f, sensibility, 0.0f);
		cameraMoved = true;
	}
	if (innerSystemInput.GetKeyDown(left))
	{
		camera->Translate(-sensibility, 0.0f, 0.0f);
		cameraMoved = true;
	}
	if (innerSystemInput.GetKeyDown(right))
	{
		camera->Translate(sensibility, 0.0f, 0.0f);
		cameraMoved = true;
	}

	if (cameraMoved)
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

