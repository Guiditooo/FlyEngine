#ifndef BASEGAME_H
#define BASEGAME_H

#include <iostream>
#include <list>

#include "Exports/Exports.h"
#include "Renderer/Renderer.h"

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

		void InternalInit();
		void InternalUpdate();
		void InternalDraw();
		void InternalDeinit();

		void CreateBuffers(Buffer& buffers);

		void AddToObjectList(Entities::Entity* newRenderizableObject);//Cambiar a component
		void ReOrderRenderizableList();
		void DrawObjects();

	public:
		BaseGame();
		~BaseGame();

		void RunGame();
		bool IsGameRunning();
		void SetWindowParameters(int width, int height, std::string name = "FlyEngine");

		void ToggleClosingWithEsc();

	protected:
		std::string initialWindowName;
		int initialWindowWidth;
		int initialWindowHeight;

		Window* window;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Deinit() = 0;

	};

}

#endif // !