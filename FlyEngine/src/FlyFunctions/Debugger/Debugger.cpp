#include "Debugger.h"
#include <iostream>
#include <string>

namespace FlyEngine
{

	namespace Utils
	{
		long Debugger::messageID = 0;

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

		void Debugger::ConsoleMessageID(const char* text, short beforeSpacesCount, short afterSpacesCount, short beforeEndlCount, short afterEndlCount)
		{
			for (short i = 0; i < beforeEndlCount; i++)
				std::cout << std::endl;

			std::cout << std::to_string(messageID) << "_";

			for (short i = 0; i < beforeSpacesCount; i++)
				std::cout << " ";

			std::cout << text;

			for (short i = 0; i < afterSpacesCount; i++)
				std::cout << " ";

			for (short i = 0; i < afterEndlCount; i++)
				std::cout << std::endl;

			messageID++;

		}

	}

}