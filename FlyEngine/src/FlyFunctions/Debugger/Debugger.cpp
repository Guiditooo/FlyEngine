#include <iostream>

#include <glm/glm.hpp>

#include "Debugger.h"
#include <string>

#include <TextureManager/TextureManager.h>

using namespace glm;

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

		void Debugger::ConsoleMessage(const char* text)
		{
			ConsoleMessage(text, 1, 0, 1, 0);
		}
		void Debugger::ConsoleMessage(std::string name, bool isActive)
		{
			name += isActive ? " is On!" : " is Off!";
			ConsoleMessage(&name[0], 1, 0, 1, 0);
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

		void Debugger::ConsoleMessage(const char* initialMsg, glm::vec3 vector3)
		{
			ConsoleMessage(initialMsg, vector3, 1, 0, 1, 0);
		}

		void Debugger::ConsoleMessage(const char* initialMsg, double value)
		{
			ConsoleMessage(initialMsg, static_cast<float>(value));
		}

		void Debugger::ConsoleMessage(const char* initialMsg, float value)
		{
			std::string text = initialMsg;
			text += ": ";
			text += std::to_string(value);

			ConsoleMessage(&text[0], 1, 0, 1, 0);
		}

		void Debugger::ConsoleMessage(const char* initialMsg, vec3 vector3, short beforeSpacesCount, short afterSpacesCount, short beforeEndlCount, short afterEndlCount)
		{
			std::string text = initialMsg;
			text += "(";
			text += std::to_string(vector3.x);
			text += ", ";
			text += std::to_string(vector3.y);
			text += ", ";
			text += std::to_string(vector3.z);
			text += ")";
			ConsoleMessage(&text[0], beforeSpacesCount, afterSpacesCount, beforeEndlCount, afterEndlCount);
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

		void Debugger::ConsoleMessageID(const char* initialMsg, glm::vec3 vector3, short beforeSpacesCount, short afterSpacesCount, short beforeEndlCount, short afterEndlCount)
		{
			std::string text = initialMsg;
			text += "(";
			text += std::to_string(vector3.x);
			text += ", ";
			text += std::to_string(vector3.y);
			text += ", ";
			text += std::to_string(vector3.z);
			text += ")";
			ConsoleMessageID(&text[0], beforeSpacesCount, afterSpacesCount, beforeEndlCount, afterEndlCount);
		}

		void Debugger::ConsoleMessageTextureCreation(int textureID)
		{
			//Creada texture id <textID> [Width x Height]

			using namespace Managers;

			TextureData t = TextureManager::GetTexture(textureID);

			std::string text = "Created Texture ID=";
			text += std::to_string(textureID);
			text += " [";
			text += std::to_string(t.texture->GetWidth());
			text += " x ";
			text += std::to_string(t.texture->GetHeight());
			text += "] Named \"";
			text += t.textureName;
			text += "\"!";

			ConsoleMessageID(&text[0], 0, 1, 0, 1);
		}

	}

}