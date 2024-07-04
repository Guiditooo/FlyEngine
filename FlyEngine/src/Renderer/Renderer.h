#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader/Shader.h"

#include "VertexAttribute/VertexAttribute.h"
#include "FlyFunctions/Color/Color.h"
#include "Buffers/Buffers.h"

#include "Texture/Texture.h"

#include "Lights/PointLight/PointLight.h"
#include "Lights/SpotLight/SpotLight.h"
#include "Lights/DirectionalLight/DirectionalLight.h"

namespace FlyEngine
{
	using namespace Utils;

	namespace Entities
	{
		class Entity;
	}

	class Renderer
	{
	private:
		Shader* primitiveShader;

		Texture* specularTexture;
		Texture* diffuseTexture;

		Color* bgColor;

	public:
		Renderer();
		~Renderer();

		void DrawObject(Entities::Entity* toDraw);//Pasar a component, porque quizas quiero UI
		void UseTextures(GLenum textureType, GLuint textureID);

		void SetBackgroundColor(Color* newBgColor);
		Color* GetBackgroundColor();

		void CreateBaseBuffers(Utils::Buffer& buffers);
		void BindBuffers(Utils::Buffer& buffers, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize);
		void BindBuffers(Utils::Buffer& buffers, const std::vector<float>& vertices, unsigned int vertexSize, const std::vector<unsigned int>& index, unsigned int indexSize);
		void SetVertexAttributes(std::vector<Utils::VertexAttribute> vertexAttributes);

		void SetMatrix4Uniform(const char* variableName, glm::mat4x4 matrix);
		void SetMatrix3Uniform(const char* variableName, glm::mat3x3 matrix);
		void SetMatrix2Uniform(const char* variableName, glm::mat2x2 matrix);

		void SetVec4Uniform(const char* variableName, glm::vec4 vec);
		void SetVec4Uniform(const char* variableName, float x, float y, float z, float w);

		void SetVec3Uniform(const char* variableName, glm::vec3 vec);
		void SetVec3Uniform(const char* variableName, float x, float y, float z);

		void SetVec2Uniform(const char* variableName, glm::vec2 vec);
		void SetVec2Uniform(const char* variableName, float x, float y);

		void SetFloatUniform(const char* variableName, float value);
		void SetBoolUniform(const char* variableName, bool value);
		void SetIntUniform(const char* variableName, int value);

		void DrawRequest(Utils::Buffer buffers, unsigned int indexCount);

		void SetSpotLight(Lights::SpotLight* light);
		void SetPointLight(Lights::PointLight* light, int index);
		void SetDirectionalLight(Lights::DirectionalLight* light);

		void SetNewShader(Shader* newShader);
	};
}

#endif // !RENDERER_H