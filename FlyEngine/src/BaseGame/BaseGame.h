#ifndef BASEGAME_H
#define BASEGAME_H

#include <iostream>
#include <list>
#include <unordered_map>

#include "Exports/Exports.h"

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Camera/Camera.h"

#include "Lights/Light.h"
#include "Rectangle/Rectangle.h"
#include "Triangle/Triangle.h"
#include "Cube/Cube.h"
#include "Material/Material.h"

namespace FlyEngine
{
	class Window;
	class MaterialSpecification;

	class FLY_API BaseGame
	{
	private:
		Renderer* renderer;
		std::list<Entities::Entity*> entityList;
		std::list<Texture*> textureList;
		std::list<Lights::Light*> lightList;

		Lights::DirectionalLight* directionalLight;

		std::unordered_map<std::string, Materials::Material*> materialsMap;

		bool isRunning;
		bool checkEsc;

		void SwapBuffers();

		void SetUpOpenGlFunctions();

		void CreateBuffers(Buffer* buffers);
		void BindBuffers(Buffer* buffers, std::vector<float> vertex, std::vector<unsigned int> index);
		void SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes);

		void AddToObjectList(Entities::Entity* newRenderizableObject);//Cambiar a component

		void CreateDefaultMaterial();

		void DrawObjects();
		void DrawEntities();
		void DrawTextures();

		void CalculateLights();

		void SetMatrixUniforms(glm::mat4 entityMatrix);
		void SetLightUniforms(Lights::Light* light, int index);
		void SetMaterialUniforms(Entities::Entity* entity);

		float PixelsToEngine(int objectWidthInPixels, float windowDimension);

		void InternalInit();
		void InternalUpdate();
		void InternalDraw();
		void InternalDeinit();

	public:
		BaseGame();
		~BaseGame();

		void RunGame();
		bool IsGameRunning();
		void SetWindowParameters(int width, int height, std::string name = "FlyEngine");

		glm::vec2 GetWindowSize();

		Camera* GetMainCamera();

		void ToggleClosingWithEsc();

		Texture* CreateTexture(const char* path);

		Materials::Material* CreateMaterial(std::string name);

		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width, float height);
		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width);
		Entities::Triangle* CreateTriangle(float posX, float posY, float posZ, float base, float height);
		Entities::Cube* CreateCube(float posX, float posY, float posZ, float width);

		Lights::DirectionalLight* CreateDirectionalLight(glm::vec3 direction = glm::vec3(0, -1, 0));
		Lights::PointLight* CreatePointLight(glm::vec3 position = glm::vec3(0, 0, 0));
		Lights::SpotLight* CreateSpotLight
		(
			glm::vec3 position = glm::vec3(0, 0, 0),
			glm::vec3 direction = glm::vec3(0, -1, 0),
			float cutOff = glm::cos(glm::radians(12.5f)),
			float outerCutOff = glm::cos(glm::radians(15.0f))
		);

	protected:
		std::string initialWindowName;
		int initialWindowWidth;
		int initialWindowHeight;

		Window* window;
		Camera* mainCamera;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Deinit() = 0;

	};

}

#endif // !