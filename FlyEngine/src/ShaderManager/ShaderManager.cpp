#include "ShaderManager.h"

const char* DEFAULT_VERTEX_PATH = "res/Shaders/defaultVertex.shader";
const char* DEFAULT_FRAGMENT_PATH = "res/Shaders/defaultFragment.shader";



namespace FlyEngine
{
	namespace Managers
	{		
		std::string ShaderManager::DEFAULT_SHADER_NAME = "DefaultShader";
		std::string ShaderManager::MODEL_SHADER_NAME = "ModelShader";

		std::unordered_map<std::string, Shader*> ShaderManager::shaderMap;

		Shader* ShaderManager::CreateShader(std::string name, const char* fPath, const char* vPath, const char* gPath)
		{
			shaderMap[name] = new Shader(name, fPath, vPath, gPath);
			return shaderMap[name];
		}

		Shader* ShaderManager::GetShader(std::string shaderName)
		{
			auto it = shaderMap.find(shaderName);
			if (it != shaderMap.end())
			{
				return it->second;
			}
			return nullptr;
		}

		Shader* ShaderManager::GetDefaultShader()
		{
			return GetShader(DEFAULT_SHADER_NAME);
		}

		void ShaderManager::InitializeManager()
		{
			CreateShader(DEFAULT_SHADER_NAME, DEFAULT_FRAGMENT_PATH, DEFAULT_VERTEX_PATH);
		}

	}
}