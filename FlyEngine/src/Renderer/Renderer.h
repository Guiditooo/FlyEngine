#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <FlyFunctions/Color/Color.h>
#include <Attribute/VertexAttribute.h>

using namespace FLY_ENGINE;

class Entity;

class Renderer
{
private:
	static Color* bgColor;

	static std::list<Entity*> renderizableObjectList;
	static void ReOrderRenderizableList();


public:
	static void DrawRenderizableObjects();
	static void AddToRenderizableList(Entity* newRenderizableObject);

	static void SetBackgroundColor(Color* newBgColor);
	static Color* GetBackgroundColor();

	static void CreateBaseBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	static void BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize);
	static void SetVertexAttributes(VertexAttribute vertexAttributes[], unsigned int vertexAttributesSize);

	static void DrawRequest(unsigned int VAO, unsigned int indexCount);

};

#endif // !