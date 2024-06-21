#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Cube.h"
#include "Renderer/Renderer.h"
#include "VertexAttribute/VertexAttribute.h"

namespace FlyEngine
{
	namespace Entities
	{

		Cube::Cube() : Entity3D ("Cube")
		{
			material = new Material();

			vertex =
			{
				-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, //0 ARRIBA IZQ FRENTE
				 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, //1 ARRIBA DER FRENTE
				-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, //2 ABAJO  IZQ FRENTE
				 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, //3 ABAJO  DER FRENTE
				   
				-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, //4 ARRIBA IZQ DETRAS
				 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, //5 ARRIBA DER DETRAS
				-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, //6 ABAJO  IZQ DETRAS
				 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  //7 ABAJO  DER DETRAS
			};

			index =
			{
				0, 1, 2, //FRENTE 
				1, 3, 2, //FRENTE
				1, 7, 3, //DERECHA
				1, 5, 7, //DERECHA
				0, 1, 4, //ARRIBA
				1, 5, 4, //ARRIBA
				
				4, 5, 6, //DETRAS 
				5, 7, 6, //DETRAS
				2, 3, 6, //ABAJO
				3, 7, 6, //ABAJO
				0, 4, 6, //IZQUIERDA
				0, 6, 2  //IZQUIERDA

			};

			indexCount = 36;
			vertexCount = 12;
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

			//Utils::Debugger::ConsoleMessage("Rectangle Created!", 2, 0, 1, 1);

			PrintCreationMsg();
		}

		Cube::~Cube()
		{
			if (material != nullptr)
			{
				delete material;
				material = nullptr;
			}
		}

		void Cube::Draw()
		{
			//Deprecated
		}

	}
}