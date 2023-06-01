#include "Debugger.h"
#include <iostream>

FLY_ENGINE::Debugger::Debugger()
{
}

FLY_ENGINE::Debugger::~Debugger()
{
}

void FLY_ENGINE::Debugger::ConsoleMessage(const char* text, short beforeSpacesCount, short afterSpacesCount, short beforeEndlCount, short afterEndlCount)
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
