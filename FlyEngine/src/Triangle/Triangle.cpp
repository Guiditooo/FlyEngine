#include <iostream>

#include <GLFW/glfw3.h>

#include "Triangle.h"
#include "VertexAttribute/VertexAttribute.h"
#include "Renderer/Renderer.h"


namespace FlyEngine
{

	namespace Entities
	{

		Triangle::Triangle()
		{

			name = "Triangle";

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

			indexCount = 6;
			vertexCount = 2;
			vertexSize = 6;

			//Renderer::CreateBaseBuffers(VAO, VBO, EBO);
			//Renderer::BindBuffers(VAO, VBO, EBO, vertex, sizeof(vertex), index, sizeof(index));

			for (short i = 0; i < vertexCount; i++)
			{
				VertexAttribute va;
				va.elementSize = 3;
				va.variableType = GL_FLOAT;
				va.isNormalized = GL_FALSE;
				va.sizeOfVertex = sizeof(float) * indexCount;
				va.offset = i * sizeof(float) * 3;
				vertexAttributes.push_back(va);
			}

			//Renderer::SetVertexAttributes(vertexAttributes, vertexCount);
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
			//Deprecated
			/*
			material->Apply();
			Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
			Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
			Renderer::DrawRequest(VAO, indexCount);
			*/
		}

	}

}