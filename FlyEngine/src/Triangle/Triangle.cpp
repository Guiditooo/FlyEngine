#include "Triangle.h"

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "VertexAttribute/VertexAttribute.h"
#include "Material/Material.h"
#include "Renderer/Renderer.h"


namespace FlyEngine
{

	namespace Entities
	{

		Triangle::Triangle() : Shape("Triangle")
		{

			const unsigned int floatSize = sizeof(float);
			const unsigned int vertexStride = (3 + 3 + 2 + 3) * floatSize;

			VertexAttribute va;

			name = "Triangle";

			material = nullptr;

			vertex = 
			{
			//  Posición                Color             UV           Normal
				 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f, // ARRIBA
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, // DER
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f  // IZQ
			};

			index =
			{
				2,0,1
			};

			indexCount = index.size();
			vertexCount = 3;
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

			//Renderer::SetVertexAttributes(vertexAttributes, vertexCount);

			PrintCreationMsg();
		}

		Triangle::~Triangle()
		{
			if (material != nullptr)
			{
				delete material;
				material = nullptr;
			}
		}

	}

}