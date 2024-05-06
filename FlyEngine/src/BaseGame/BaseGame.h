#ifndef BASEGAME_H
#define BASEGAME_H

#include <Exports/Exports.h>
#include <iostream>

namespace FlyEngine
{

	class Window;

	class FLY_API BaseGame
	{
	private:
		bool isRunning;
		bool checkEsc;

		void SwapBuffers();

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