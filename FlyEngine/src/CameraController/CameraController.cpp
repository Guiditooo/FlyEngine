#include <string>

#include "CameraController.h"
#include "FlyFunctions/Debugger/Debugger.h"

FlyEngine::Utils::Input innerSystemInput;

FlyEngine::CameraController::CameraController(Camera* camera, Window* window)
{
	this->camera = camera;

	sensibility = 0.15f;

	cameraRotation = CameraRotation();

	isFirst = true;

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

FlyEngine::Camera* FlyEngine::CameraController::GetCamera()
{
	return camera;
}

void FlyEngine::CameraController::Update(bool showMessage)
{
	bool cameraMoved = false;

	if (isFirst)
	{
		
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
		{
			camera->MoveForward(sensibility);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_S))
		{
			camera->MoveBackward(sensibility);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_SPACE))
		{
			camera->MoveUp(sensibility);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			camera->MoveDown(sensibility);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_A))
		{
			camera->MoveLeft(sensibility);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_D))
		{
			camera->MoveRight(sensibility);
			cameraMoved = true;
		}

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_I))
		{
			camera->Rotate(1, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_K))
		{
			camera->Rotate(-1, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_J))
		{
			camera->Rotate(0.0f, 1, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_L))
		{
			camera->Rotate(0.0f, -1, 0.0f);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_U))
		{
			camera->Rotate(0.0f, 0.0f, 1);
			cameraMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_O))
		{
			camera->Rotate(0.0f, 0.0f, -1);
			cameraMoved = true;
		}
	}
	else
	{
		//3ra personas
		//Movimiento al rededor de la entidad elegida con la distancia elegida.
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

