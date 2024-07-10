#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <iostream>
#include <unordered_map>

#include "Shader/Shader.h"

namespace FlyEngine
{
	namespace Managers
	{

		class FLY_API ShaderManager
		{
		private:
			static std::unordered_map<std::string, Shader*> shaderMap;
		public:
			static std::string DEFAULT_SHADER_NAME;
			static std::string MODEL_SHADER_NAME;
			static Shader* CreateShader(std::string name, const char* fPath, const char* vPath, const char* gPath = nullptr);
			static Shader* GetShader(std::string shaderName);
			static Shader* GetDefaultShader();
			
			static void InitializeManager();
		};

	}
}
#endif // !SHADER_MANAGER_H