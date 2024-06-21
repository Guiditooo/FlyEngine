#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include "VertexAttribute/VertexAttribute.h"
#include "FlyFunctions/Color/Color.h"
#include "Buffers/Buffers.h"

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
		Color* bgColor;

		void ReOrderRenderizableList();

	public:
		Renderer();
		~Renderer();
		
		void DrawObject(Entities::Entity* toDraw);//Pasar a component, porque quizas quiero UI

		void SetBackgroundColor(Color* newBgColor);
		Color* GetBackgroundColor();

		void CreateBaseBuffers(Utils::Buffer& buffers);
		void BindBuffers(Utils::Buffer& buffers, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize);
		void BindBuffers(Utils::Buffer& buffers, const std::vector<float>& vertices, unsigned int vertexSize, const std::vector<unsigned int>& index, unsigned int indexSize);
		void SetVertexAttributes(std::vector<Utils::VertexAttribute> vertexAttributes);

		void SetMatrixUniform(unsigned int shaderID, const char* variableName, glm::mat4x4 matrix);
		void SetVec3Uniform(unsigned int shaderID, const char* variableName, glm::vec3 vec);

		void DrawRequest(Utils::Buffer buffers, unsigned int indexCount);

	};
}

#endif // !