#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Rectangle.h"
#include "Renderer/Renderer.h"
#include "VertexAttribute/VertexAttribute.h"

namespace FlyEngine
{
	namespace Entities
	{

		Rectangle::Rectangle() : Shape("Rectangle")
		{

			indexCount = 6;
			vertexCount = 2;
			vertexSize = 6;

			material = new Material();

			vertex =
			{
				-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA IZQ
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA DER
				-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ABAJO IZQ
				 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f  //ABAJO DER
			};

			index =
			{
				2,0,1,
				2,3,1
			};
			
			for (short i = 0; i < vertexCount; i++)
			{
				VertexAttribute va;
				va.elementSize = 3;
				va.variableType = GL_FLOAT;
				va.isNormalized = GL_FALSE;
				va.sizeOfVertex = sizeof(float) * indexCount;
				va.offset = i * sizeof(float) * va.elementSize;
				vertexAttributes.push_back(va);
			}

			//Renderer::CreateBaseBuffers(VAO, VBO, EBO);
			//Renderer::BindBuffers(VAO, VBO, EBO, vertex, sizeof(vertex), index, sizeof(index));
			//Renderer::SetVertexAttributes(vertexAttributes, vertexCount);

			//Utils::Debugger::ConsoleMessage("Rectangle Created!", 2, 0, 1, 1);

			PrintCreationMsg();
		}
		 
		Rectangle::~Rectangle()
		{
			if (material != nullptr)
			{
				delete material;
				material = nullptr;
			}
		}

		/*int Rectangle::GetRectangleCount()
		{
			return rectangleCount;
		}*/

		void Rectangle::Draw()
		{
			//Deprecated - Lo hago en el BaseGame
			/*
			//std::cout << " Estoy dibujando un cuadrao \n";
			material->Apply();
			Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
			Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
			Renderer::DrawRequest(VAO, indexCount);
			*/
		}

	}

}