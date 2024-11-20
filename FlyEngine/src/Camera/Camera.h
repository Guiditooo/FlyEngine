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


		float fov; // = 45.0f;  // Campo de visión en grados
		float aspectRatio; //= screenWidth / screenHeight; Relación de aspecto (ancho / alto de la ventana)
		float nearPlane; //= 0.1f;  // Plano cercano
		float farPlane; //= 100.0f;  // Plano lejano

		void SetCamera(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetDefaultCamera();

	public:
		Camera();
		Camera(glm::vec3 pos);
		Camera(ProjectionType projType, float fov, float aspectRatio, float nearPlane, float farPlane);
		~Camera();

		glm::mat4 projMatrix; //cambiar
		glm::mat4 viewMatrix;

		void Update();

		void SetProjectionType(ProjectionType projType);
		void SetFoV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetPlanes(float nearPlane, float farPlane);

		glm::mat4 GetProjMatrix();
		glm::mat4 GetViewMatrix();

		void Translate(float x, float y, float z);
		void Rotate(float x, float y, float z);

		void WorldRotate(float x, float y, float z);
		void WorldRotate(glm::vec3 rot);

		void SetPosition(float x, float y, float z) override;
		void SetRotation(float x, float y, float z) override;
	};
}

#endif // !CAMERA_H
