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
			const unsigned int floatSize = sizeof(float);
			const unsigned int vertexStride = (3 + 3 + 2 + 3) * floatSize;
			// 3 para posición, 3 para color, 2 para UV, 3 para normal
			
			VertexAttribute va;
			
			material = new Materials::Material();

			vertex = 
			{
				// Position          Color             UV	        Normal
				// Front
				-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f, // 0
				 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, // 1
				-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f, // 2
				 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f, // 3

				// Back
			    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f, // 4
				 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f, // 5
				-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, // 6
				 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f, // 7

				// Left
				-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, // 8
				-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, // 9
				-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f, // 10
				-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, // 11

				// Right
				 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f, // 12
				 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, // 13
				 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f, // 14
				 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, // 15

				// Top
				-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, // 16
			 	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f, // 17
				-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, // 18
				 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f, // 19

				// Bot
				-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, // 20
				 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // 21
				-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, // 22
				 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // 23
			};

			index = 
			{
				// Front
				0, 1, 2,
				1, 3, 2,

				// Back
				4, 6, 5,
				5, 6, 7,

				// Left
				8, 9, 10,
				10, 9, 11,

				// Right
				12, 14, 13,
				13, 14, 15,

				// Top
				16, 18, 17,
				17, 18, 19,

				// Bot
				20, 21, 22,
				21, 23, 22,
			};			

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