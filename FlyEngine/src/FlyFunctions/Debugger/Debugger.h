#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Exports/Exports.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//typedef glm::mat4;
//typedef glm::vec3;


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
			static void ConsoleMessage(std::string name, bool isActive);
			static void ConsoleMessage(const char* initialMsg, glm::vec3 vector3);
			static void ConsoleMessage(const char* text, short beforeSpacesCount, short afterSpacesCount = 1, short beforeEndlCount = 0, short afterEndlCount = 1);
			static void ConsoleMessage(const char* initialMsg, glm::vec3 vector3, short beforeSpacesCount, short afterSpacesCount = 1, short beforeEndlCount = 0, short afterEndlCount = 1);
			static void ConsoleMessageID(const char* text, short beforeSpacesCount = 0, short afterSpacesCount = 1, short beforeEndlCount = 0, short afterEndlCount = 1);
			static void ConsoleMessageID(const char* initialMsg, glm::vec3 vector3, short beforeSpacesCount = 0, short afterSpacesCount = 1, short beforeEndlCount = 0, short afterEndlCount = 1);

		};

	}

}

#endif // !DEBUGGER_H
