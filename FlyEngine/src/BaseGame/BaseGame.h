#ifndef BASEGAME_H
#define BASEGAME_H

#include <iostream>
#include <list>

#include "Exports/Exports.h"

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Camera/Camera.h"

#include "Rectangle/Rectangle.h"
#include "Triangle/Triangle.h"
#include "Cube/Cube.h"

namespace FlyEngine
{
	class Window;

	class FLY_API BaseGame
	{
	private:
		Renderer renderer;
		std::list<Entities::Entity*> entityList;

		bool isRunning;
		bool checkEsc;

		void SwapBuffers();

		void CreateBuffers(Buffer* buffers);
		void BindBuffers(Buffer* buffers, std::vector<float> vertex, std::vector<unsigned int> index);
		void SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes);

		void AddToObjectList(Entities::Entity* newRenderizableObject);//Cambiar a component
		void DrawObjects();

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

		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width, float height);
		Entities::Rectangle* CreateRectangle(float posX, float posY, float posZ, float width);
		Entities::Triangle* CreateTriangle(float posX, float posY, float posZ, float base, float height);
		Entities::Cube* CreateCube(float posX, float posY, float posZ,float width);

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