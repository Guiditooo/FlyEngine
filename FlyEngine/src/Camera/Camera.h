#ifndef CAMERA_H
#define CAMERA_H

#include <Entity/Entity.h>


namespace FlyEngine
{
	class Window;
	
	enum class ProjectionType
	{
		Ortho,
		Perspective
	};

	class FLY_API Camera : public Entities::Entity
	{
	private:
		ProjectionType projectionType;

		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;

		float fov; // = 45.0f;  // Campo de visión en grados
		float aspectRatio; //= screenWidth / screenHeight; Relación de aspecto (ancho / alto de la ventana)
		float nearPlane; //= 0.1f;  // Plano cercano
		float farPlane; //= 100.0f;  // Plano lejano

		//float sensitivity;// = 0.1f; // Sensibilidad del movimiento del ratón

		//void ProcessMouseMovement(float moveX, float moveY);
		//void MouseMovementCallback(GLFWwindow* window, double mouseX, double mouseY);


	public:
		Camera(Window* window, ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		Camera(Window* window);
		~Camera();

		void Draw() override;
		void Update();

		void SetProjectionType(ProjectionType projType);
		void SetFoV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetPlanes(float nearPlane, float farPlane);

	};
}

#endif // !CAMERA_H
