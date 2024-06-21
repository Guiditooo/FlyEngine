#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Exports/Exports.h>

typedef glm::mat4;
typedef glm::vec3;

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

			static void ConsoleMessage(const char* text);
			static void ConsoleMessage(const char* initialMsg, glm::vec3 vector3);
			static void ConsoleMessage(const char* text, short beforeSpacesCount, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);
			static void ConsoleMessage(const char* initialMsg, glm::vec3 vector3, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);
			static void ConsoleMessageID(const char* text, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);
			static void ConsoleMessageID(const char* initialMsg, glm::vec3 vector3, short beforeSpacesCount = 0, short afterSpacesCount = 0, short beforeEndlCount = 0, short afterEndlCount = 0);

		};

	}

}

#endif // !DEBUGGER_H
