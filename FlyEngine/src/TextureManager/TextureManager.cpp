#include "TextureManager.h"

#include "TextureImporter/TextureImporter.h"
#include "FlyFunctions/Debugger/Debugger.h"

const char* DEFAULT_TEXTURE_PATH = "res/Textures";
const char* DEFAULT_TEXTURE_NAME = "BlankTexture";
 
namespace FlyEngine
{
	//using namespace Importers;
	using namespace Utils;

	namespace Managers
	{

		std::unordered_map<std::string, Texture*> TextureManager::textureMap;

		void TextureManager::CreateDefaultTexture()
		{
			CreateTexture(DEFAULT_TEXTURE_NAME, DEFAULT_TEXTURE_PATH);
		}

		void TextureManager::InitializeManager()
		{
			CreateDefaultTexture();
		}
		int TextureManager::CreateTexture(std::string textureName, const char* path)
		{
			int txID = GetTextureID(textureName);
			if (txID != -1)
			{
				std::string text = "Texture [" + textureName + "] already created!";
				Debugger::ConsoleMessage(&text[0]);
				return txID;
			}
			
			textureMap[textureName] = Importers::TextureImporter::SearchTexture(path, textureName, true);

			std::string text = "Texture Created: [" + textureName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);

			return txID;
		}

		int TextureManager::CreateSearchedTexture(std::string directory, std::string filename, std::string textureName, bool sendMessage)
		{
			int txID = GetTextureID(textureName);
			if (GetTextureID(textureName) != -1)
			{
				std::string text = "Texture [" + textureName + "] already created!";
				Debugger::ConsoleMessage(&text[0]);
				return txID;
			}

			textureMap[textureName] = Importers::TextureImporter::SearchTexture(directory, filename, false);

			std::string text = "Texture Created: [" + textureName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);
			
			return txID;
		}

		int TextureManager::GetTextureID(std::string textureName)
		{
			auto it = textureMap.find(textureName);
			if (it != textureMap.end())
			{
				return it->second->GetID();
			}
			return -1;
		}

		int TextureManager::GetDefaultTextureID()
		{
			return GetTextureID(DEFAULT_TEXTURE_NAME);
		}

		Texture* TextureManager::GetDefaultTexture()
		{
			return textureMap[DEFAULT_TEXTURE_NAME];
		}

		Texture* TextureManager::GetTexture(std::string textureName)
		{
			return textureMap[textureName];
		}

		void TextureManager::SetTextureType(int textureID, std::string type)
		{
			int key = -1; // Valor de clave por defecto si no se encuentra

			for (const auto& pair : textureMap)
			{
				if (pair.second->GetID() == textureID)
				{
					pair.second->SetType(type);
					key = pair.second->GetID();
					break;
				}
			}

			if (key == -1)
				Debugger::ConsoleMessage("The provided Texture ID is not loaded!");
		}

		void TextureManager::BindTexture(int textureID, unsigned int slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		void TextureManager::UnBindTexture()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

}