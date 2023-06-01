#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Exports/Exports.h>


namespace FLY_ENGINE
{
	class FLY_API Debugger
	{
	public:
		Debugger();
		~Debugger();

		static void ConsoleMessage(const char* text, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);

	};

}

#endif // !DEBUGGER_H
