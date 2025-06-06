#ifndef BASEGAME_H
#define BASEGAME_H

#include <iostream>
#include <list>

#include "Exports/Exports.h"

#include "Renderer/Renderer.h"
#include "Camera/Camera.h"

#include "Material/Material.h"
#include "CameraController/CameraController.h"
#include "Lights/Light.h"
#include "Rectangle/Rectangle.h"
#include "Triangle/Triangle.h"
#include "Cube/Cube.h"
#include "Sprite/Sprite.h"
#include "ShaderManager/ShaderManager.h"
#include "EngineMode/EngineMode.h"

namespace FlyEngine
{
	class FLY_API BaseGame
	{
	private:
		Renderer* renderer;

		std::list<Entities::Model*> modelList;
		std::list<Entities::Entity3D*> entity3DList;
		std::list<Entities::Entity2D*> entity2DList;
		std::list<Entities::Sprite*> spriteList;
		std::list<Lights::Light*> lightList;

		Lights::DirectionalLight* directionalLight;

		CameraController* cameraController;

		const int MAX_POINT_LIGHTS = 4;

		bool isRunning;
		bool checkEsc;

		bool using3DEntities;
		bool using2DEntities;
		bool calculatingLights;

		void SwapBuffers();

		void SetUpOpenGlFunctions();

		void CreateBuffers(Buffers* buffers);
		void BindBuffers(Buffers* buffers, std::vector<float> vertex, std::vector<unsigned int> index);
		void SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes);

		void AddToObjectList(Entities::Entity* newRenderizableObject);//Cambiar a component

		void DrawObjects();
		void DrawModel(Entities::Model* model);
		void DrawModels();
		void DrawModelRecursive(Entities::Model* model);
		void Draw2DEntities();
		void Draw3DEntities();
		//void DrawSceneGraph(SceneGraph* sceneGraph);
		void DrawTextures();

		void CalculateLights();

		void SetMatrixUniforms(Entities::Entity* entity);
		void SetLightUniforms(Lights::Light* light, int index, unsigned int shaderID = Managers::ShaderManager::GetDefaultModelShader()->GetShaderID());
		void SetMaterialUniforms(Entities::Entity* entity);

		float PixelsToEngine(int objectWidthInPixels, float windowDimension);

		void GetMouseMovement();

		void InternalInit();
		void InternalUpdate();
		void InternalDraw();
		void InternalDeinit();

		float FindMiddleNumber(float a, float b, float c);

	public:
		BaseGame();
		~BaseGame();

		void RunGame();
		bool IsGameRunning();
		void SetWindowParameters(int width, int height, std::string name = "FlyEngine");

		glm::vec2 GetWindowSize();

		Camera* GetMainCamera();

		void SetBSP(bool isActive);

		void ToggleClosingWithEsc();

		Texture* CreateTexture(const char* path);

		CameraController* CreateCameraController(Camera* controllingCamera, float translateSens, float rotationSens, CameraMode cameraMode, Entities::Entity* target = nullptr, float followDistance = 0.0f);//Replaces the old one

		Entities::Model* CreateModel(std::string const& path, std::string name = "Model");

		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width, float height);
		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width);
		Entities::Triangle* CreateTriangle(float posX, float posY, float posZ, float base, float height);
		Entities::Cube* CreateCube(float posX, float posY, float posZ, float width);

		Entities::Sprite* CreateSprite(const char* path, bool creationMessage = false);

		Lights::DirectionalLight* CreateDirectionalLight(glm::vec3 direction = glm::vec3(0, -1, 0));
		Lights::PointLight* CreatePointLight(glm::vec3 position = glm::vec3(0, 0, 0));
		Lights::SpotLight* CreateSpotLight
		(
			glm::vec3 position = glm::vec3(0, 0, 0),
			glm::vec3 direction = glm::vec3(0, -1, 0),
			float cutOff = glm::cos(glm::radians(12.5f)),
			float outerCutOff = glm::cos(glm::radians(15.0f))
		);

		Lights::DirectionalLight* GetDirectionalLight();

		void ShowCursor();
		void HideCursor();

		void Toggle3DEntityEnabled(bool value);
		void Toggle2DEntityEnabled(bool value);
		void ToggleLightCalculations(bool value);

		void SetEngineMode(EngineMode mode);

	protected:
		std::string initialWindowName;
		int initialWindowWidth;
		int initialWindowHeight;

		Window* window;
		Camera* mainCamera;

		EngineMode engineMode;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Deinit() = 0;

	};

}

#endif // !BASE_GAME