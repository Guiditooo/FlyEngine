#include "Renderer.h"

#include <vector>
#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "TextureManager/TextureManager.h"
#include "ShaderManager/ShaderManager.h"
#include "MaterialManager/MaterialManager.h"

#include "Entity/Entity.h"
#include "Sprite/Sprite.h"
#include "Model/Model.h"
#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "MaterialSpecification/MaterialSpecification.h"

//#include "SceneGraph/SceneGraph.h"

#include "Scene/Scene.h"

namespace FlyEngine
{

	using namespace Managers;

	Renderer::Renderer()
	{
		bgColor = new Color(COLOR::FLYBLACK);

		TextureManager::InitializeManager();
		ShaderManager::InitializeManager();
		MaterialManager::InitializeManager();
	}

	Renderer::~Renderer()
	{

	}
	void Renderer::DrawObject(Entities::Entity* toDraw)
	{

	}
	/*
	void Renderer::DrawSceneGraph(SceneGraph* sceneGraph)
	{
		for (auto& node : sceneGraph->GetNodes())
		{
			DrawNode(node, glm::mat4(1.0f)); // Pasamos una matriz identidad como transformación inicial
		}
	}

	void BaseGame::DrawNode(SceneNode* node, const glm::mat4& parentTransform)
	{
		// Acumulamos la transformación del nodo con la de su padre
		glm::mat4 currentTransform = parentTransform * node->GetLocalTransform();

		if (node->GetEntity()->IsActive())
		{
			if (auto model = dynamic_cast<Entities::Model*>(node->GetEntity()))
			{
				// Setear las matrices de vista y proyección y demás propiedades
				renderer->DrawModel(model, mainCamera->GetViewMatrix(), mainCamera->GetProjMatrix(), mainCamera->GetTransform()->GetPosition(), currentTransform);
			}
			else
			{
				// Caso de otros tipos de entidades
				auto entity = node->GetEntity();
				if (!entity->IsCameraTarget())
				{
					entity->UseShader();
					SetMatrixUniforms(entity, currentTransform);  // Mandamos la transformación acumulada

					SetMaterialUniforms(entity);

					renderer->SetVec3Uniform(entity->GetShaderID(), "baseColor", entity->GetMaterial()->GetColorV3());
					renderer->SetVec3Uniform(entity->GetShaderID(), "entityColor", entity->GetColorV3());
					renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
				}
			}
		}

		// Llamada recursiva para cada hijo del nodo actual
		for (auto& child : node->GetChildren())
		{
			DrawNode(child, currentTransform);
		}
	}
	*/

	void Renderer::DrawModel(Entities::Model* toDraw, glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 camPos)
	{
		if (!toDraw->IsActive())
			return;

		std::string modelName = toDraw->GetRoot()->GetName();
		bool a = modelName == "BP";

		std::vector<Mesh*> meshes = toDraw->GetMeshes();

		for (int i = 0; i < meshes.size(); i++)
		{
			unsigned int id;
			Materials::Material* renderingMat = nullptr;

			toDraw->UseShader();
			id = toDraw->GetShaderID();

			renderingMat = toDraw->GetMaterial();
			std::string matName = renderingMat->GetName();
			bool b = matName == "BP_mat";

			if (renderingMat == nullptr || Managers::MaterialManager::GetMaterial(renderingMat->GetName()) == nullptr)
			{
				renderingMat = MaterialManager::GetDefaultMissingMaterial();
			}

			if (id == ShaderManager::GetDefaultModelShader()->GetShaderID())
				SetVec3Uniform(id, "viewPos", camPos);

			SetMatrix4Uniform(id, "view", viewMat);
			SetMatrix4Uniform(id, "projection", projMat);
			SetMatrix4Uniform(id, "model", toDraw->GetModelMatrix());

			SetVec3Uniform(id, "baseColor", renderingMat->GetColorV3());
			SetVec3Uniform(id, "entityColor", toDraw->GetRoot()->GetColorV3());

			DrawMesh(meshes[i], renderingMat);
		}
	}

	void Renderer::DrawTexture(Entities::Sprite* sprite)
	{
		glActiveTexture(GL_TEXTURE0);
		TextureManager::BindTexture(sprite->GetTexture());
		SetIntUniform(sprite->GetShaderID(), "theTexture", 0);
		glActiveTexture(GL_TEXTURE0);
	}

	void Renderer::DrawScene(Scene* toDraw, glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 camPos)
	{
		toDraw->Traverse([&](Entities::Entity* entity)
			{
				Entities::Model* model = dynamic_cast<Entities::Model*>(entity);
				if (model == nullptr)
					return;
				if (model->IsActive())
				{
					DrawModel(model, viewMat, projMat, camPos);
				}
			});
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
		SetBoolUniform(shaderID, "spotLight.isActive", light->IsActive());
		SetVec3Uniform(shaderID, "spotLight.ambient", light->GetAmbient());
		SetVec3Uniform(shaderID, "spotLight.specular", light->GetSpecular());
		SetVec3Uniform(shaderID, "spotLight.diffuse", light->GetDiffuse());
		SetVec3Uniform(shaderID, "spotLight.position", light->GetPosition());
		SetVec3Uniform(shaderID, "spotLight.direction", light->GetDirection());
		SetVec3Uniform(shaderID, "spotLight.lightColor", light->GetColor().GetColorV3());
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

	void Renderer::DrawMesh(Mesh* mesh, Materials::Material* mat)
	{
		std::vector<std::string> order = mat->GetTextureOrder();

		for (unsigned int i = 0; i < order.size(); i++)
		{
			std::string base = "material.";

			std::string uniformVariable = base;
			uniformVariable += order[i];

			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			int txID = mat->GetTexture(order[i]);

			TextureManager::BindTexture(txID, i);

			SetIntUniform(mat->GetShaderID(), &uniformVariable[0], i);
		}

		SetFloatUniform(mat->GetShaderID(), "material.shininess", mat->GetSpecs()->GetShininess());

		// draw mesh
		DrawRequest(*(mesh->GetBuffers()), mesh->GetIndexes().size());

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);

	}
}