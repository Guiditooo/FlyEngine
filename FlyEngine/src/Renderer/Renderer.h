#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <FlyFunctions/Color/Color.h>
#include <Attribute/VertexAttribute.h>
#include <glm/glm.hpp>

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
		static Color* bgColor;

		static std::list<Entities::Entity*> renderizableObjectList;
		static void ReOrderRenderizableList();

		static glm::mat4 view;

	public:
		static void DrawRenderizableObjects();
		static void AddToRenderizableList(Entities::Entity* newRenderizableObject);

		static void SetBackgroundColor(Color* newBgColor);
		static Color* GetBackgroundColor();

		static void CreateBaseBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		static void BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize);
		static void SetVertexAttributes(VertexAttribute vertexAttributes[], unsigned int vertexAttributesSize);

		static void SetMatrixUniform(unsigned int shaderID, const char* variableName, glm::mat4x4 matrix);
		static void SetVec3Uniform(unsigned int shaderID, const char* variableName, glm::vec3 vec);

		static void DrawRequest(unsigned int VAO, unsigned int indexCount);

	};

}

#endif // !