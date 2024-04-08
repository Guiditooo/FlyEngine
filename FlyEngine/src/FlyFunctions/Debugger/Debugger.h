#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Exports/Exports.h>


namespace FlyEngine
{
	namespace Utils
	{

		class FLY_API Debugger
		{
		private:
			static long messageID;
		public:
			Debugger();
			~Debugger();

			static void ConsoleMessage(const char* text, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);
			static void ConsoleMessageID(const char* text, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);

		};

	}

}

#endif // !DEBUGGER_H
