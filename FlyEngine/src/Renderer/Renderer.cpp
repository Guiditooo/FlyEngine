#include "Renderer.h"
#include <Entity/Entity.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

std::list<Entity*> Renderer::renderizableObjectList;
Color* Renderer::bgColor;

void Renderer::DrawRenderizableObjects()
{
	for (Entity* renderizableObject : renderizableObjectList)		
	{
		if (renderizableObject->IsActive())
		{
			renderizableObject->Draw();
		}
	}	
}

#pragma region ORDER RENDERIZABLE OBJECTS

bool CompareByDrawLayer(Entity* a, Entity* b)
{
	return a->GetDrawLayer() < b->GetDrawLayer();
}

void Renderer::ReOrderRenderizableList()
{
	renderizableObjectList.sort(CompareByDrawLayer);
}

#pragma endregion

void Renderer::AddToRenderizableList(Entity* newRenderizableObject)
{
	renderizableObjectList.push_back(newRenderizableObject);
}


void Renderer::SetBackgroundColor(Color* newBgColor)
{
	bgColor = newBgColor;
	glClearColor(bgColor->GetColor().r, bgColor->GetColor().g, bgColor->GetColor().b, bgColor->GetColor().a);

	glClear(GL_COLOR_BUFFER_BIT);
}

Color* Renderer::GetBackgroundColor()
{
	return bgColor;
}

void Renderer::CreateBaseBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Renderer::BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
}

void Renderer::SetVertexAttributes(VertexAttribute vertexAttributes[], unsigned int vertexAttributesSize)
{
	for (short i = 0; i < vertexAttributesSize; i++)
	{
		unsigned int size = vertexAttributes[i].elementSize;
		unsigned int type = vertexAttributes[i].variableType;
		unsigned int normalized = vertexAttributes[i].isNormalized;
		unsigned int stride = vertexAttributes[i].sizeOfVertex;
		unsigned int offset = vertexAttributes[i].offset;

		glVertexAttribPointer(i, size, type, normalized, stride, (void*)offset);
		glEnableVertexAttribArray(i);
	}
}

void Renderer::DrawRequest(unsigned int VAO, unsigned int indexCount)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}