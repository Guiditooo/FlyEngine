#include "Sprite.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "VertexAttribute/VertexAttribute.h"
#include "TextureManager/TextureManager.h"

namespace FlyEngine
{
	namespace Entities
	{
		int Sprite::internalID = 1;

		Sprite::Sprite(const char* path, bool creationMessage) : Entity2D("Sprite")
		{
			const unsigned int floatSize = sizeof(float);
			const unsigned int vertexStride = (3 + 3 + 2 + 3) * floatSize;

			Utils::VertexAttribute va;

			material = nullptr;

			vertex =
			{
				//	Position            Color             UV		  Normal
					-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //ARRIBA IZQ
					 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //ARRIBA DER
					-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //ABAJO IZQ
					 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  //ABAJO DER
			};

			index =
			{
				2,0,1,
				2,3,1
			};

			indexCount = index.size();
			vertexCount = 4;

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

			textureCode = "Sprite";
			textureCode += std::to_string(internalID);

			texture = Managers::TextureManager::CreateTexture(textureCode, path, true);

			Managers::TextureData t = Managers::TextureManager::GetTexture(texture);

			width = t.texture->GetWidth();
			height = t.texture->GetHeight();

			if(creationMessage)	
				PrintCreationMsg();

			internalID++;
		}

		SpriteDims Sprite::GetDimentions()
		{
			return { width, height };
		}

		int Sprite::GetTexture()
		{
			return texture;
		}

		Sprite::~Sprite()
		{

		}

	}
}