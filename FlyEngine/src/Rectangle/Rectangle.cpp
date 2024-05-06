#include "Rectangle.h"
#include "Renderer/Renderer.h"
#include "Attribute/VertexAttribute.h"
#include "FlyFunctions/Debugger/Debugger.h"

#include <iostream>

const int INDEX_COUNT = 6;
const int VERTEX_COUNT = 2;
const int VERTEX_SIZE = 6;

namespace FlyEngine
{
	namespace Entities
	{

		Rectangle::Rectangle()
		{

			name = "Rectangle";

			material = new Material();

			float vertex[] =
			{
				-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA IZQ
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ARRIBA DER
				-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //ABAJO IZQ
				 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f  //ABAJO DER
			};

			unsigned int index[] =
			{
				2,0,1,
				2,3,1
			};

			Renderer::CreateBaseBuffers(VAO, VBO, EBO);
			Renderer::BindBuffers(VAO, VBO, EBO, vertex, sizeof(vertex), index, sizeof(index));

			VertexAttribute vertexAttributes[VERTEX_COUNT];

			for (short i = 0; i < VERTEX_COUNT; i++)
			{
				vertexAttributes[i].elementSize = 3;
				vertexAttributes[i].variableType = GL_FLOAT;
				vertexAttributes[i].isNormalized = GL_TRUE;
				vertexAttributes[i].sizeOfVertex = sizeof(float) * VERTEX_SIZE;
				vertexAttributes[i].offset = i * sizeof(float) * 3;
			}

			Renderer::SetVertexAttributes(vertexAttributes, VERTEX_COUNT);

			Utils::Debugger::ConsoleMessage("Rectangle Created!", 2, 0, 1, 1);
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
			//std::cout << " Estoy dibujando un cuadrao \n";
			material->Apply();
			Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
			Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
			Renderer::DrawRequest(VAO, INDEX_COUNT);
		}

	}

}