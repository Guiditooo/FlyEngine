#include "Renderer.h"

#include <vector>
#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Entity/Entity.h"
#include "TextureImporter/TextureImporter.h"

namespace FlyEngine
{
	using namespace Importers;

	const char* DEFAULT_VERTEX_PATH = "res/Shaders/vertex.shader";
	const char* DEFAULT_FRAGMENT_PATH = "res/Shaders/fragment.shader";

	Renderer::Renderer()
	{
		bgColor = new Color(COLOR::FLYBLACK);
		primitiveShader = new Shader(DEFAULT_FRAGMENT_PATH, DEFAULT_VERTEX_PATH);
		primitiveShader->UseShader();
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


	void Renderer::SetNewShader(Shader* newShader)
	{
		primitiveShader = newShader;
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

	void Renderer::UseTextures(GLenum textureType, GLuint textureID)
	{
		glActiveTexture(textureType);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Renderer::SetMatrix4Uniform(const GLchar* variableName, glm::mat4x4 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetMatrix3Uniform(const GLchar* variableName, glm::mat3x3 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniformMatrix3fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetMatrix2Uniform(const GLchar* variableName, glm::mat2x2 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniformMatrix2fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetVec4Uniform(const char* variableName, glm::vec4 vec)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform4f(uniformLocation, vec.x, vec.y, vec.z, vec.w);
	}

	void Renderer::SetVec4Uniform(const char* variableName, float x, float y, float z, float w)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform4f(uniformLocation, x, y, z, w);
	}

	void Renderer::SetVec3Uniform(const char* variableName, glm::vec3 vec)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
	}

	void Renderer::SetVec3Uniform(const char* variableName, float x, float y, float z)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform3f(uniformLocation, x, y, z);
	}

	void Renderer::SetVec2Uniform(const char* variableName, glm::vec2 vec)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform2f(uniformLocation, vec.x, vec.y);
	}

	void Renderer::SetVec2Uniform(const char* variableName, float x, float y)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform2f(uniformLocation, x, y);
	}

	void Renderer::SetFloatUniform(const char* variableName, float value)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform1f(uniformLocation, value);
	}

	void Renderer::SetBoolUniform(const char* variableName, bool value)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform1i(uniformLocation, (int)value);
	}

	void Renderer::SetIntUniform(const char* variableName, int value)
	{
		GLint uniformLocation = glGetUniformLocation(primitiveShader->GetShaderID(), variableName);
		glUniform1i(uniformLocation, (int)value);
	}

	void Renderer::SetSpotLight(Lights::SpotLight* light)
	{
		SetBoolUniform("spotLight.isActive", light->IsActive());
		SetVec3Uniform("spotLight.ambient", light->GetAmbient());
		SetVec3Uniform("spotLight.specular", light->GetSpecular());
		SetVec3Uniform("spotLight.diffuse", light->GetDiffuse());
		SetVec3Uniform("spotLight.position", light->GetPosition());
		SetVec3Uniform("spotLight.direction", light->GetDirection());
		SetFloatUniform("spotLight.constant", light->GetConstant());
		SetFloatUniform("spotLight.linear", light->GetLinear());
		SetFloatUniform("spotLight.quadratic", light->GetQuadratic());
		SetFloatUniform("spotLight.cutOff", light->GetCutOff());
		SetFloatUniform("spotLight.outerCutOff", light->GetOuterCutOff());
	}

	void Renderer::SetPointLight(Lights::PointLight* light, int index)
	{
		std::string text;
		std::string base = "pointLights[";
		base += std::to_string(index);
		base += "].";

		text = base;
		text += "ambient";
		SetVec3Uniform(&text[0], light->GetAmbient());

		text = base;
		text += "specular";
		SetVec3Uniform(&text[0], light->GetSpecular());

		text = base;
		text += "diffuse";
		SetVec3Uniform(&text[0], light->GetDiffuse());

		text = base;
		text += "position";
		SetVec3Uniform(&text[0], light->GetPosition());

		text = base;
		text += "constant";
		SetFloatUniform(&text[0], light->GetConstant());

		text = base;
		text += "linear";
		SetFloatUniform(&text[0], light->GetLinear());

		text = base;
		text += "quadratic";
		SetFloatUniform(&text[0], light->GetQuadratic());

		text = base;
		text += "isActive";
		SetBoolUniform(&text[0], light->IsActive());
	}

	void Renderer::SetDirectionalLight(Lights::DirectionalLight* light)
	{
		SetBoolUniform("dirLight.isActive", light->IsActive());
		SetVec3Uniform("dirLight.ambient", light->GetAmbient());
		SetVec3Uniform("dirLight.specular", light->GetSpecular());
		SetVec3Uniform("dirLight.diffuse", light->GetDiffuse());
		SetVec3Uniform("dirLight.direction", light->GetDirection());
	}

}