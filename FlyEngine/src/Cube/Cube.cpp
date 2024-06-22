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

		Cube::Cube() : Entity3D("Cube")
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
				// Cara frontal
				0, 1, 2,
				1, 3, 2,

				// Cara trasera
				4, 6, 5,
				5, 6, 7,

				// Cara izquierda
				0, 2, 4,
				4, 2, 6,

				// Cara derecha
				1, 5, 3,
				5, 7, 3,

				// Cara superior
				0, 4, 1,
				1, 4, 5,

				// Cara inferior
				2, 3, 6,
				3, 7, 6
			};

			indexCount = index.size();
			vertexCount = 8;
			vertexSize = 6;

			for (short i = 0; i < vertexCount; i++)
			{
				VertexAttribute va;
				va.elementSize = 3;
				va.variableType = GL_FLOAT;
				va.isNormalized = GL_FALSE;
				va.sizeOfVertex = sizeof(float) * vertexSize;
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