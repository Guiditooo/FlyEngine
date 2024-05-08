#include "Renderer.h"
#include <Entity/Entity.h>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

namespace FlyEngine
{
	Renderer::Renderer()
	{
		bgColor = new Color(COLOR::FLYBLACK);
		projectionMat = glm::mat4(1);
		viewMat = glm::mat4(1);
	}

	Renderer::~Renderer()
	{
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

	void Renderer::CreateBaseBuffers(Utils::Buffer& buffers)
	{
		glGenVertexArrays(1, &buffers.VAO);
		glGenBuffers(1, &buffers.VBO);
		glGenBuffers(1, &buffers.EBO);
	}

	void Renderer::BindBuffers(Utils::Buffer& buffers, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize)
	{
		glBindVertexArray(buffers.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	}

	void Renderer::SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes)
	{
		for (short i = 0; i < vertexAttributes.size(); i++)
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

	void Renderer::DrawRequest(Utils::Buffer buffers, unsigned int indexCount)
	{
		glBindVertexArray(buffers.VAO);
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