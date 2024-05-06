#include "Camera.h"

#include <Window/Window.h>
#include "Input/Input.h"

namespace FlyEngine
{

	const float MOUSE_SENSIBILITY = 0.1f;

	Camera::Camera(Window* window,
		ProjectionType projType = ProjectionType::Perspective,
		float fov = 45.0f, float aspectRatio = 800.0f / 600.0f,
		float nearPlane = 0.1f, float farPlane = 100.0f)
	{
		this->projectionType = projType;
		this->fov = fov;
		this->aspectRatio = aspectRatio;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;

		if (projectionType == ProjectionType::Perspective)
			projMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		else
			projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, nearPlane, farPlane);

		viewMatrix = glm::mat4(1);

		//Utils::Input::OnMouseMovementCallback(ProcessMouseMovement, rotation.yaw, rotation.pitch);
	}
	Camera::Camera(Window* window)
	{
		this->projectionType = ProjectionType::Perspective;
		this->fov = 45.0f;
		this->aspectRatio = 800.0f / 600.0f;
		this->nearPlane = 0.1f;
		this->farPlane = 100.0f;

		if (projectionType == ProjectionType::Perspective)
			projMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		else
			projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, nearPlane, farPlane);

		viewMatrix = glm::mat4(1);

		//Utils::Input::OnMouseMovementCallback(ProcessMouseMovement, rotation.yaw, rotation.pitch);
	}
	/*
	void Camera::ProcessMouseMovement(float moveX, float moveY)
	{
		moveX *= sensitivity;
		moveY *= sensitivity;

		// Actualizar los ángulos de yaw y pitch
		rotation.yaw += moveX;
		rotation.pitch += moveY;

		// Limitar el ángulo de pitch para evitar volteos excesivos
		if (rotation.pitch > 89.0f)
			rotation.pitch = 89.0f;
		
		if (rotation.pitch < -89.0f)
			rotation.pitch = -89.0f;
		
	}
	*/
	/*
	void MouseMovementCallback(GLFWwindow* window, double mouseX, double mouseY)
		//Lo saco de la clase para evitar problemas de scopes
	{
		static float lastX = 0.0f;
		static float lastY = 0.0f;
		static bool firstMove = true;

		if (firstMove)
		{
			lastX = mouseX;
			lastY = mouseY;
			firstMove = false;
		}

		float moveX = mouseX - lastX;
		float moveY = lastY - mouseY; // Invierte el desplazamiento del ratón para que la cámara no se invierta
		lastX = mouseX;
		lastY = mouseY;

		moveX *= MOUSE_SENSIBILITY;
		moveY *= MOUSE_SENSIBILITY;

		ProcessMouseMovement(moveX, moveY);
	}
	*/
	Camera::~Camera()
	{

	}

	void Camera::Draw()
	{
		//Se dibuja la camara? No
		//Asi que esto va a cambiar cuando transforme el engine
		//en component-model
	}

	void Camera::Update()
	{

	}

	void Camera::SetProjectionType(ProjectionType projectionType)
	{
		this->projectionType = projectionType;
	}

	void Camera::SetFoV(float fov)
	{
		this->fov = fov;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}

	void Camera::SetPlanes(float nearPlane, float farPlane)
	{
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;

	}

}