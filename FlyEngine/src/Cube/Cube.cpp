#include "Cube.h"
#include "Rectangle/Rectangle.h"
#include "Renderer/Renderer.h"
#include "Attribute/VertexAttribute.h"
#include "FlyFunctions/Debugger/Debugger.h"

#include <iostream>

const int INDEX_COUNT = 36;
const int VERTEX_COUNT = 12;
const int VERTEX_SIZE = 6;

namespace FlyEngine
{
	namespace Entities
	{

		Cube::Cube()
		{
			name = "Cube";

			material = new Material();

			float vertex[] =
			{
				-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0 ARRIBA IZQ FRENTE
				 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, //1 ARRIBA DER FRENTE
				-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //2 ABAJO  IZQ FRENTE
				 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f  //3 ABAJO  DER FRENTE
				   
				-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //4 ARRIBA IZQ DETRAS
				 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //5 ARRIBA DER DETRAS
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //6 ABAJO  IZQ DETRAS
				 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f  //7 ABAJO  DER DETRAS
			};

			unsigned int index[] =
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
			//std::cout << " Estoy dibujando un cubo \n";
			material->Apply();
			Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
			Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
			Renderer::DrawRequest(VAO, INDEX_COUNT);
		}

	}
}