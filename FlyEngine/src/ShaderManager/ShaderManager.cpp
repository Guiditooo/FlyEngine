#include "ShaderManager.h"

const char* DEFAULT_MODEL_VERTEX_PATH = "res/Shaders/defaultModelVertex.shader";
const char* DEFAULT_MODEL_FRAGMENT_PATH = "res/Shaders/defaultModelFragment.shader";

const char* DEFAULT_BASIC_VERTEX_PATH = "res/Shaders/defaultBasicVertex.shader";
const char* DEFAULT_BASIC_FRAGMENT_PATH = "res/Shaders/defaultBasicFragment.shader";

const char* BASIC_SHADER_NAME = "BasicShader";
const char* MODEL_SHADER_NAME = "ModelShader";

namespace FlyEngine
{
	namespace Managers
	{		

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

		Shader* ShaderManager::GetDefaultBasicShader()
		{
			return GetShader(BASIC_SHADER_NAME);
		}

		Shader* ShaderManager::GetDefaultModelShader()
		{
			return GetShader(MODEL_SHADER_NAME);
		}

		void ShaderManager::InitializeManager()
		{
			CreateShader(BASIC_SHADER_NAME, DEFAULT_BASIC_FRAGMENT_PATH, DEFAULT_BASIC_VERTEX_PATH);
			CreateShader(MODEL_SHADER_NAME, DEFAULT_MODEL_FRAGMENT_PATH, DEFAULT_MODEL_VERTEX_PATH);
		}

	}
}