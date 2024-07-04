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
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::SetBackgroundColor(Color* newBgColor)
	{
		bgColor = newBgColor;
		glm::vec4 bgVector = bgColor->GetColorV4();

		glClearColor(bgVector.r, bgVector.g, bgVector.b, bgVector.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	void Renderer::BindBuffers(Utils::Buffer& buffers, const std::vector<float>& vertices, unsigned int vertexSize, const std::vector<unsigned int>& index, unsigned int indexSize)
	{
		glBindVertexArray(buffers.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(float), index.data(), GL_STATIC_DRAW);
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

	void Renderer::DrawRequest(Utils::Buffer buffers, unsigned int indexCount)
	{
		glBindVertexArray(buffers.VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void Renderer::SetMatrixUniform(unsigned int shaderID, const GLchar* variableName, glm::mat4x4 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetVec3Uniform(unsigned int shaderID, const char* variableName, glm::vec3 vec)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		//glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
		glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
	}

	void Renderer::SetFloatUniform(unsigned int shaderID, const char* variableName, float value)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform1f(uniformLocation, value);
	}

	void Renderer::SetSpotLight(unsigned int shaderID, Lights::SpotLight* light)
	{
		SetBaseLightUniforms(shaderID, light);
	}

	void Renderer::SetPointLight(unsigned int shaderID, Lights::PointLight* light)
	{
		SetBaseLightUniforms(shaderID, light);
		SetFloatUniform(shaderID, "light.constant", light->GetConstant());
		SetFloatUniform(shaderID, "light.linear", light->GetLinear());
		SetFloatUniform(shaderID, "light.quadratic", light->GetQuadratic());
	}

	void Renderer::SetDirectionalLight(unsigned int shaderID, Lights::DirectionalLight* light)
	{
		SetBaseLightUniforms(shaderID, light);
	}

	void Renderer::SetBaseLightUniforms(unsigned int shaderID, Lights::Light* light)
	{
		SetVec3Uniform(shaderID, "light.ambient", light->GetAmbient());
		SetVec3Uniform(shaderID, "light.specular", light->GetSpecular());
		SetVec3Uniform(shaderID, "light.diffuse", light->GetDiffuse());
	}

}