#include "CameraController.h"
#include "Window/Window.h"

FlyEngine::Utils::Input innerSystemInput;

FlyEngine::CameraController::CameraController(Window* window, KeyCode forward, KeyCode backward, KeyCode up, KeyCode down, KeyCode left, KeyCode right)
{
	camera = new Camera(window, FlyEngine::ProjectionType::Perspective, 45.0f, 1920.0f / 1080, 0.0f, 100.0f);
	
	this->forward = forward;
	this->backward = backward;
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;

	innerSystemInput = FlyEngine::Utils::Input(window);
}

FlyEngine::CameraController::~CameraController()
{
	delete camera;
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

void FlyEngine::CameraController::Update()
{
	if (innerSystemInput.GetKeyDown(forward))
	{
		camera->Translate(0.0f, 0.0f, 0.01f);
	}
	if (innerSystemInput.GetKeyDown(backward))
	{
		camera->Translate(0.0f, 0.0f, -0.01f);
	}
	if (innerSystemInput.GetKeyDown(up))
	{
		camera->Translate(0.0f, -0.01f, 0.0f);
	}
	if (innerSystemInput.GetKeyDown(down))
	{
		camera->Translate(0.0f, 0.01f, 0.0f);
	}
	if (innerSystemInput.GetKeyDown(left))
	{
		camera->Translate(-0.01f, 0.0f, 0.0f);
	}
	if (innerSystemInput.GetKeyDown(right))
	{
		camera->Translate(0.01f, 0.0f, 0.0f);
	}
}
