#include "Renderer.h"

#include <vector>
#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager/ShaderManager.h"
#include "MaterialManager/MaterialManager.h"

#include "Entity/Entity.h"
#include "Model/Model.h"
#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "MaterialSpecification/MaterialSpecification.h"

namespace FlyEngine
{

	using namespace Managers;

	const char* MODEL_VERTEX_PATH = "res/Shaders/modelVertex.shader";
	const char* MODEL_FRAGMENT_PATH = "res/Shaders/modelFragment.shader";

	Renderer::Renderer()
	{
		bgColor = new Color(COLOR::FLYBLACK);

		ShaderManager::InitializeManager();
		MaterialManager::InitializeManager();

		ShaderManager::CreateShader(ShaderManager::MODEL_SHADER_NAME, MODEL_FRAGMENT_PATH, MODEL_VERTEX_PATH);

	}

	Renderer::~Renderer()
	{
		
	}
	void Renderer::DrawObject(Entities::Entity* toDraw)
	{

	}

	void Renderer::DrawModel(Entities::Model* toDraw, glm::mat4x4 viewMat, glm::mat4x4 projMat, glm::vec3 camPos)
	{
		std::vector<Entities::Mesh*> meshes = toDraw->GetMeshes();
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->UseShader();
			unsigned int id = meshes[i]->GetShaderID();

			SetMatrix4Uniform(id, "view", viewMat);
			SetMatrix4Uniform(id, "projection", projMat);
			SetMatrix4Uniform(id, "model", meshes[i]->GetModelMatrix());
			SetVec3Uniform(id, "viewPos", camPos);

			DrawMesh(meshes[i], toDraw->GetName());
		}
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

	void Renderer::CreateBaseBuffers(Utils::Buffers& buffers)
	{
		glGenVertexArrays(1, &buffers.VAO);
		glGenBuffers(1, &buffers.VBO);
		glGenBuffers(1, &buffers.EBO);
	}

	void Renderer::BindBuffers(Utils::Buffers& buffers, float* vertices, unsigned int vertexSize, unsigned int* index, unsigned int indexSize)
	{
		glBindVertexArray(buffers.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	}

	void Renderer::BindBuffers(Utils::Buffers& buffers, const std::vector<float>& vertices, unsigned int vertexSize, const std::vector<unsigned int>& index, unsigned int indexSize)
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

	void Renderer::DrawRequest(Utils::Buffers buffers, unsigned int indexCount)
	{
		glBindVertexArray(buffers.VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Renderer::UseTextures(GLenum textureType, GLuint textureID)
	{
		glActiveTexture(textureType);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glActiveTexture(GL_TEXTURE0);
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

	void Renderer::SetSpotLight(Lights::SpotLight* light, unsigned int shaderID)
	{
		SetBoolUniform( shaderID, "spotLight.isActive", light->IsActive());
		SetVec3Uniform( shaderID, "spotLight.ambient", light->GetAmbient());
		SetVec3Uniform( shaderID, "spotLight.specular", light->GetSpecular());
		SetVec3Uniform (shaderID, "spotLight.diffuse", light->GetDiffuse());
		SetVec3Uniform( shaderID, "spotLight.position", light->GetPosition());
		SetVec3Uniform( shaderID, "spotLight.direction", light->GetDirection());
		SetVec3Uniform( shaderID, "spotLight.lightColor", light->GetColor().GetColorV3());
		SetFloatUniform(shaderID, "spotLight.constant", light->GetConstant());
		SetFloatUniform(shaderID, "spotLight.linear", light->GetLinear());
		SetFloatUniform(shaderID, "spotLight.quadratic", light->GetQuadratic());
		SetFloatUniform(shaderID, "spotLight.cutOff", light->GetCutOff());
		SetFloatUniform(shaderID, "spotLight.outerCutOff", light->GetOuterCutOff());
	}

	void Renderer::SetPointLight(Lights::PointLight* light, int index, unsigned int shaderID)
	{
		std::string text;
		std::string base = "pointLights[";
		base += std::to_string(index);
		base += "].";

		text = base;
		text += "ambient";
		SetVec3Uniform(shaderID, &text[0], light->GetAmbient());

		text = base;
		text += "specular";
		SetVec3Uniform(shaderID, &text[0], light->GetSpecular());

		text = base;
		text += "diffuse";
		SetVec3Uniform(shaderID, &text[0], light->GetDiffuse());

		text = base;
		text += "position";
		SetVec3Uniform(shaderID, &text[0], light->GetPosition());

		text = base;
		text += "constant";
		SetFloatUniform(shaderID, &text[0], light->GetConstant());

		text = base;
		text += "linear";
		SetFloatUniform(shaderID, &text[0], light->GetLinear());

		text = base;
		text += "quadratic";
		SetFloatUniform(shaderID, &text[0], light->GetQuadratic());

		text = base;
		text += "isActive";
		SetBoolUniform(shaderID, &text[0], light->IsActive());

		text = base;
		text += "lightColor";
		SetVec3Uniform(shaderID, &text[0], light->GetColor().GetColorV3());
	}

	void Renderer::SetDirectionalLight(Lights::DirectionalLight* light, unsigned int shaderID)
	{
		SetBoolUniform(shaderID, "dirLight.isActive", light->IsActive());
		SetVec3Uniform(shaderID, "dirLight.direction", light->GetDirection());
		SetVec3Uniform(shaderID, "dirLight.ambient", light->GetAmbient());
		SetVec3Uniform(shaderID, "dirLight.specular", light->GetSpecular());
		SetVec3Uniform(shaderID, "dirLight.diffuse", light->GetDiffuse());
		SetVec3Uniform(shaderID, "dirLight.lightColor", light->GetColor().GetColorV3());
	}

	void Renderer::DrawMesh(Entities::Mesh* mesh, std::string modelName)
	{

		std::vector<std::string> order = mesh->GetMaterial()->GetTextureOrder();

		for (unsigned int i = 0; i < order.size(); i++)
		{
			std::string base = "material.";

			std::string uniformVariable = base;
			uniformVariable += order[i];

			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

			Texture* tx = mesh->GetMaterial()->GetTexture(order[i]);

			tx->Bind(i);
			SetIntUniform(mesh->GetShaderID(), &uniformVariable[0], i);
		}
		
		SetFloatUniform(mesh->GetShaderID(), "material.shininess", 64/*mesh->GetMaterial()->GetSpecs()->GetShininess()*/);

		// draw mesh
		DrawRequest(*(mesh->GetBuffers()), mesh->GetIndexes().size());

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);

	}
}