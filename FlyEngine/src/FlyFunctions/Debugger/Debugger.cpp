#include "Debugger.h"
#include <iostream>

namespace FlyEngine
{

	namespace Utils
	{

		Debugger::Debugger()
		{
		}

		Debugger::~Debugger()
		{
		}

		void Debugger::ConsoleMessage(const char* text, short beforeSpacesCount, short afterSpacesCount, short beforeEndlCount, short afterEndlCount)
		{
			for (short i = 0; i < beforeEndlCount; i++)
				std::cout << std::endl;

			for (short i = 0; i < beforeSpacesCount; i++)
				std::cout << " ";

			std::cout << text;

			for (short i = 0; i < afterSpacesCount; i++)
				std::cout << " ";

			for (short i = 0; i < afterEndlCount; i++)
				std::cout << std::endl;
		}

	}

}