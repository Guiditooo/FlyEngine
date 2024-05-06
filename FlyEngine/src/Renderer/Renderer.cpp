#include "Renderer.h"
#include <Entity/Entity.h>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

namespace FlyEngine
{

	std::list<Entities::Entity*> Renderer::renderizableObjectList;
	Color* Renderer::bgColor;

	void Renderer::DrawRenderizableObjects()
	{
		for (Entities::Entity* renderizableObject : renderizableObjectList)
		{
			if (renderizableObject->IsActive())
			{
				renderizableObject->Draw();
			}
		}
	}

	glm::mat4 Renderer::viewMat;
	glm::mat4 Renderer::projectionMat;

#pragma region ORDER RENDERIZABLE OBJECTS

	bool CompareByDrawLayer(Entities::Entity* a, Entities::Entity* b)
	{
		return a->GetDrawLayer() < b->GetDrawLayer();
	}

	void Renderer::ReOrderRenderizableList()
	{
		renderizableObjectList.sort(CompareByDrawLayer);
	}

#pragma endregion

	void Renderer::AddToRenderizableList(Entities::Entity* newRenderizableObject)
	{
		renderizableObjectList.push_back(newRenderizableObject);
	}


	void Renderer::SetBackgroundColor(Color* newBgColor)
	{
		bgColor = newBgColor;
		glClearColor(bgColor->GetColorV4().r, bgColor->GetColorV4().g, bgColor->GetColorV4().b, bgColor->GetColorV4().a);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	Color* Renderer::GetBackgroundColor()
	{
		return bgColor;
	}

	void Renderer::CreateBaseBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void Renderer::BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	}

	void Renderer::SetVertexAttributes(VertexAttribute vertexAttributes[], unsigned int vertexAttributesSize)
	{
		for (short i = 0; i < vertexAttributesSize; i++)
		{
			unsigned int size = vertexAttributes[i].elementSize;
			unsigned int type = vertexAttributes[i].variableType;
			unsigned int normalized = vertexAttributes[i].isNormalized;
			unsigned int stride = vertexAttributes[i].sizeOfVertex;
			unsigned int offset = vertexAttributes[i].offset;

			glVertexAttribPointer(i, size, type, normalized, stride, (void*)offset);
			glEnableVertexAttribArray(i);
		}
	}

	void Renderer::AssignViewMatrix(glm::mat4 viewM)
	{
		viewMat = viewM;
	}

	void Renderer::AssignProjectionMatrix(glm::mat4 projectionM)
	{
		projectionMat = projectionM;
	}

	void Renderer::DrawRequest(unsigned int VAO, unsigned int indexCount)
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void Renderer::SetMatrixUniform(unsigned int shaderID, const char* variableName, glm::mat4x4 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint viewUniformLocation = glGetUniformLocation(shaderID, "viewMatrix");
		glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMat));

		GLint projectionUniformLocation = glGetUniformLocation(shaderID, "projectionMatrix");
		glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projectionMat));
	}

	void Renderer::SetVec3Uniform(unsigned int shaderID, const char* variableName, glm::vec3 vec)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		//glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
		glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
	}

}