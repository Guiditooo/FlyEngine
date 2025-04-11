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
			static Shader* CreateShader(std::string name, const char* fPath, const char* vPath, const char* gPath = nullptr);
			static Shader* GetShader(std::string shaderName);
			static Shader* GetDefaultBasicShader(); //CAMBIAR A ID
			static Shader* GetDefaultModelShader();
			static Shader* GetTextureShader();
			
			static void InitializeManager();
		};

	}
}
#endif // !SHADER_MANAGER_H