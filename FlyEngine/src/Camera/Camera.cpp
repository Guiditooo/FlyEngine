#include "Camera.h"

#include <Window/Window.h>
#include "Input/Input.h"

namespace FlyEngine
{
	Camera::Camera() : Entity("Camera")
	{
		SetDefaultCamera();
	}

	Camera::Camera(glm::vec3 pos) : Entity("Camera", pos)
	{
		SetDefaultCamera();
	}

	Camera::Camera(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane) : Entity("Camera")
	{
		SetCamera(projType, fov, aspectRatio, nearPlane, farPlane);
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

	void Camera::SetCamera(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		this->projectionType = projType;
		this->fov = glm::radians(fov);
		this->aspectRatio = aspectRatio;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;

		if (this->projectionType == ProjectionType::Perspective)
			projMatrix = glm::perspective(this->fov, this->aspectRatio, this->nearPlane, this->farPlane);
		else
			projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, this->nearPlane, this->farPlane);


		glm::vec3 direction = positionVector - GetFront();

		viewMatrix = glm::lookAt(positionVector, direction, GetUp());
		//viewMatrix = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		//viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

		//Utils::Input::OnMouseMovementCallback(ProcessMouseMovement, rotation.yaw, rotation.pitch);

		PrintCreationMsg();
	}

	void Camera::SetDefaultCamera()
	{
		ProjectionType projType = ProjectionType::Perspective;
		float fov = 45.0f;
		float aspectRatio = 800.0f / 600.0f;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		SetCamera(projType, fov, aspectRatio, nearPlane, farPlane);
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

	glm::mat4 Camera::GetProjMatrix()
	{
		return projMatrix;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return viewMatrix;
	}

	void Camera::Translate(float x, float y, float z)
	{
		Entity::Translate(x, y, z); 

		glm::vec3 direction = positionVector - GetFront();
		viewMatrix = glm::lookAt(positionVector, direction, GetUp());
	}

	void Camera::Rotate(float x, float y, float z)
	{
		Entity::Rotate(x, y, z);

		glm::vec3 direction = positionVector - GetFront();
		viewMatrix = glm::lookAt(positionVector, direction, GetUp());
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		Entity::SetPosition(x, y, z);

		glm::vec3 direction = positionVector - GetFront();
		viewMatrix = glm::lookAt(positionVector, direction, GetUp());
	}

	void Camera::SetRotation(float x, float y, float z)
	{
		Entity::SetRotation(x, y, z);

		glm::vec3 direction = positionVector - GetFront();
		viewMatrix = glm::lookAt(positionVector, direction, GetUp());
	}

}