#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Rectangle.h"
#include "Renderer/Renderer.h"
#include "Material/Material.h"
#include "VertexAttribute/VertexAttribute.h"

namespace FlyEngine
{
	namespace Entities
	{

		Rectangle::Rectangle() : Shape("Rectangle")
		{

			const unsigned int floatSize = sizeof(float);
			const unsigned int vertexStride = (3 + 3 + 2 + 3) * floatSize;

			VertexAttribute va;


			material = nullptr;

			vertex =
			{
				//¨Position         //Color           //UV		  //Normal
				-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //ARRIBA IZQ
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //ARRIBA DER
				-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ABAJO IZQ
				 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f //ABAJO DER
			};

			index =
			{
				2,0,1,
				2,3,1
			};

			indexCount = index.size();
			vertexCount = 4;
			//vertexSize = 6;

			//Posicion
			va.elementSize = 3;
			va.variableType = GL_FLOAT;
			va.isNormalized = GL_FALSE;
			va.sizeOfVertex = vertexStride;
			va.offset = 0;
			vertexAttributes.push_back(va);

			//Color
			va.elementSize = 3;
			va.variableType = GL_FLOAT;
			va.isNormalized = GL_FALSE;
			va.sizeOfVertex = vertexStride;
			va.offset = 3 * floatSize; //Después de la posición)
			vertexAttributes.push_back(va);

			//UV
			va.elementSize = 2;
			va.variableType = GL_FLOAT;
			va.isNormalized = GL_FALSE;
			va.sizeOfVertex = vertexStride;
			va.offset = (3 + 3) * floatSize; //Después del color)
			vertexAttributes.push_back(va);

			//Normal
			va.elementSize = 3;
			va.variableType = GL_FLOAT;
			va.isNormalized = GL_FALSE;
			va.sizeOfVertex = vertexStride;
			va.offset = (3 + 3 + 2) * floatSize; //Después del UV)
			vertexAttributes.push_back(va);

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