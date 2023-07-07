#include "Rectangle.h"
#include "Renderer/Renderer.h"
#include "Attribute/VertexAttribute.h"

#include <iostream>

const int INDEX_COUNT = 6;

//int Rectangle::rectangleCount = 0;

Rectangle::Rectangle()
{

	float vertex[] =
	{
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA IZQ
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA DER
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //ABAJO IZQ
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f  //ABAJO DER
	};
	
	unsigned int index[] = 
	{
		2,0,1,
		2,3,1
	};

	Renderer::CreateBaseBuffers(VAO, VBO, EBO);
	Renderer::BindBuffers(VAO, VBO, EBO, vertex, sizeof(vertex), index, sizeof(index));

	VertexAttribute vertexAttributes[2];

	for (short i = 0; i < 2; i++)
	{
		vertexAttributes[i].elementSize = 3;
		vertexAttributes[i].variableType = GL_FLOAT;
		vertexAttributes[i].isNormalized = GL_FALSE;
		vertexAttributes[i].sizeOfVertex = sizeof(float) * 6;
		vertexAttributes[i].offset = i * sizeof(float) * 3;
	}

	Renderer::SetVertexAttributes(vertexAttributes, 2);

}

Rectangle::~Rectangle()
{
	//rectangleCount--;
}

/*int Rectangle::GetRectangleCount()
{
	return rectangleCount;
}*/

void Rectangle::Draw()
{
	//std::cout << " Estoy dibujando un cuadrao \n";
	material->Apply();
	Renderer::DrawRequest(VAO, INDEX_COUNT);
}
