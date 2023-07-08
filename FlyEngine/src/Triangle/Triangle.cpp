#include "Triangle.h"

#include <iostream>
#include <Attribute/VertexAttribute.h>
#include <Renderer/Renderer.h>

const int INDEX_COUNT = 6;

Triangle::Triangle()
{

	material = new Material();

	float vertex[] =
	{
		   0.0f,  0.462f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA
		 0.462f, -0.462f, 0.0f, 1.0f, 1.0f, 1.0f, //DER
		-0.462f, -0.462f, 0.0f, 1.0f, 1.0f, 1.0f, //IZQ
	};

	unsigned int index[] =
	{
		2,0,1,
	};

	Renderer::CreateBaseBuffers(VAO, VBO, EBO);
	Renderer::BindBuffers(VAO, VBO, EBO, vertex, sizeof(vertex), index, sizeof(index));

	VertexAttribute vertexAttributes[2];

	for (short i = 0; i < 2; i++)
	{
		vertexAttributes[i].elementSize = 3;
		vertexAttributes[i].variableType = GL_FLOAT;
		vertexAttributes[i].isNormalized = GL_FALSE;
		vertexAttributes[i].sizeOfVertex = sizeof(float) * INDEX_COUNT;
		vertexAttributes[i].offset = i * sizeof(float) * 3;
	}

	Renderer::SetVertexAttributes(vertexAttributes, 2);
}

Triangle::~Triangle()
{
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}
}

void Triangle::Draw()
{
	material->Apply();
	Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
	Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
	Renderer::DrawRequest(VAO, INDEX_COUNT);
}
