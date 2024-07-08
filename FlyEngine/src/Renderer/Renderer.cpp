#include "Renderer.h"

#include <vector>
#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Entity/Entity.h"

#include "Model/Model.h"

namespace FlyEngine
{
	const char* DEFAULT_VERTEX_PATH = "res/Shaders/defaultVertex.shader";
	const char* DEFAULT_FRAGMENT_PATH = "res/Shaders/defaultFragment.shader";

	const char* MODEL_VERTEX_PATH = "res/Shaders/modelVertex.shader";
	const char* MODEL_FRAGMENT_PATH = "res/Shaders/modelFragment.shader";

	Renderer::Renderer()
	{
		bgColor = new Color(COLOR::FLYBLACK);

		CreateShader(DEFAULT_SHADER_NAME, DEFAULT_FRAGMENT_PATH, DEFAULT_VERTEX_PATH);
		CreateShader("ModelShader", MODEL_FRAGMENT_PATH, MODEL_VERTEX_PATH);

		actualShader = GetShader(DEFAULT_SHADER_NAME);
	}

	Renderer::~Renderer()
	{
		for (auto element : shaderMap)
		{
			if (element.second != nullptr)
			{
				delete element.second;
				element.second = nullptr;
			}
		}
	}
	void Renderer::DrawObject(Entities::Entity* toDraw)
	{

	}

	void Renderer::DrawModel(Entities::Model* toDraw)
	{
		toDraw->Draw(toDraw->GetShaderID());
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

	void Renderer::UseTextures(GLenum textureType, GLuint textureID)
	{
		glActiveTexture(textureType);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Renderer::SetMatrix4Uniform(unsigned int shaderID, const GLchar* variableName, glm::mat4x4 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetMatrix3Uniform(unsigned int shaderID, const GLchar* variableName, glm::mat3x3 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniformMatrix3fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetMatrix2Uniform(unsigned int shaderID, const GLchar* variableName, glm::mat2x2 matrix)
	{
		GLint modelUniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniformMatrix2fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Renderer::SetVec4Uniform(unsigned int shaderID, const char* variableName, glm::vec4 vec)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform4f(uniformLocation, vec.x, vec.y, vec.z, vec.w);
	}

	void Renderer::SetVec4Uniform(unsigned int shaderID, const char* variableName, float x, float y, float z, float w)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform4f(uniformLocation, x, y, z, w);
	}

	void Renderer::SetVec3Uniform(unsigned int shaderID, const char* variableName, glm::vec3 vec)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
	}

	void Renderer::SetVec3Uniform(unsigned int shaderID, const char* variableName, float x, float y, float z)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform3f(uniformLocation, x, y, z);
	}

	void Renderer::SetVec2Uniform(unsigned int shaderID, const char* variableName, glm::vec2 vec)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform2f(uniformLocation, vec.x, vec.y);
	}

	void Renderer::SetVec2Uniform(unsigned int shaderID, const char* variableName, float x, float y)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform2f(uniformLocation, x, y);
	}

	void Renderer::SetFloatUniform(unsigned int shaderID, const char* variableName, float value)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform1f(uniformLocation, value);
	}


	void Renderer::SetBoolUniform(unsigned int shaderID, const char* variableName, bool value)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform1i(uniformLocation, (int)value);
	}

	void Renderer::SetIntUniform(unsigned int shaderID, const char* variableName, int value)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, variableName);
		glUniform1i(uniformLocation, (int)value);
	}

	void Renderer::SetSpotLight(Lights::SpotLight* light)
	{
		unsigned int id = actualShader->GetShaderID();
		SetBoolUniform(id, "spotLight.isActive", light->IsActive());
		SetVec3Uniform(id, "spotLight.ambient", light->GetAmbient());
		SetVec3Uniform(id, "spotLight.specular", light->GetSpecular());
		SetVec3Uniform(id, "spotLight.diffuse", light->GetDiffuse());
		SetVec3Uniform(id, "spotLight.position", light->GetPosition());
		SetVec3Uniform(id, "spotLight.direction", light->GetDirection());
		SetFloatUniform(id, "spotLight.constant", light->GetConstant());
		SetFloatUniform(id, "spotLight.linear", light->GetLinear());
		SetFloatUniform(id, "spotLight.quadratic", light->GetQuadratic());
		SetFloatUniform(id, "spotLight.cutOff", light->GetCutOff());
		SetFloatUniform(id, "spotLight.outerCutOff", light->GetOuterCutOff());

		SetVec3Uniform(id, "spotLight.lightColor", light->GetColor().GetColorV3());
	}

	void Renderer::SetPointLight(Lights::PointLight* light, int index)
	{
		unsigned int id = actualShader->GetShaderID();
		std::string text;
		std::string base = "pointLights[";
		base += std::to_string(index);
		base += "].";

		text = base;
		text += "ambient";
		SetVec3Uniform(id, &text[0], light->GetAmbient());

		text = base;
		text += "specular";
		SetVec3Uniform(id, &text[0], light->GetSpecular());

		text = base;
		text += "diffuse";
		SetVec3Uniform(id, &text[0], light->GetDiffuse());

		text = base;
		text += "position";
		SetVec3Uniform(id, &text[0], light->GetPosition());

		text = base;
		text += "constant";
		SetFloatUniform(id, &text[0], light->GetConstant());

		text = base;
		text += "linear";
		SetFloatUniform(id, &text[0], light->GetLinear());

		text = base;
		text += "quadratic";
		SetFloatUniform(id, &text[0], light->GetQuadratic());

		text = base;
		text += "isActive";
		SetBoolUniform(id, &text[0], light->IsActive());

		text = base;
		text += "lightColor";
		SetVec3Uniform(id, &text[0], light->GetColor().GetColorV3());
	}

	void Renderer::SetDirectionalLight(Lights::DirectionalLight* light)
	{
		unsigned int id = actualShader->GetShaderID();
		SetBoolUniform(id, "dirLight.isActive", light->IsActive());
		SetVec3Uniform(id, "dirLight.direction", light->GetDirection());
		SetVec3Uniform(id, "dirLight.ambient", light->GetAmbient());
		SetVec3Uniform(id, "dirLight.specular", light->GetSpecular());
		SetVec3Uniform(id, "dirLight.diffuse", light->GetDiffuse());
		SetVec3Uniform(id, "dirLight.lightColor", light->GetColor().GetColorV3());
	}

	void Renderer::CreateShader(std::string name, const char* fPath, const char* vPath, const char* gPath)
	{
		shaderMap[name] = new Shader(fPath, vPath, name ,gPath);
	}

	Shader* Renderer::GetShader(std::string shaderName)
	{
		auto it = shaderMap.find(shaderName);
		if (it != shaderMap.end())
		{
			return it->second;
		}
		return nullptr;
	}

}