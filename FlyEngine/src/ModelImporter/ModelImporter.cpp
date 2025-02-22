#include "ModelImporter.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "MaterialManager/MaterialManager.h"
#include "ShaderManager/ShaderManager.h"
#include "TextureManager/TextureManager.h"
#include "BSPManager/BSPManager.h"

#include "TextureImporter/TextureImporter.h"
#include "Texture/Texture.h"
#include "Mesh/Mesh.h"
#include "Model/Model.h"
#include "Vertex/Vertex.h"

namespace FlyEngine
{
	namespace Importers
	{
		Entities::Model* ModelImporter::LoadModel(std::string modelName, std::string const& path, bool gamma)
		{
			Entities::Model* model = new Entities::Model(modelName);

			bool createdMaterial = false;

			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(path,
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType |
				aiProcess_FlipUVs |
				aiProcess_CalcTangentSpace |
				aiProcess_GenSmoothNormals |
				aiProcess_LimitBoneWeights |
				aiProcess_GenBoundingBoxes |
				aiProcess_GlobalScale);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return nullptr;
			}

			model->SetDirectory(path.substr(0, path.find_last_of('/')) + "/");

			ProcessNode(scene->mRootNode, scene, model, createdMaterial);

			Materials::Material* modelMaterial = Managers::MaterialManager::GetMaterial(model->GetName() + "_mat");

			if (modelMaterial != nullptr)
				model->SetMaterial(modelMaterial, true);

			// Agregar planos si el nombre del modelo contiene "BSP"
			if (modelName.find("BSP") != std::string::npos || modelName.find("bsp") != std::string::npos)
			{
				model->SetBSPModel(true);
				RegisterModelPlanes(model);
			}

			return model;
		}

		void ModelImporter::RegisterModelPlanes(Entities::Model* model)
		{
			for (auto& mesh : model->GetMeshes())
			{
				const auto& vertices = mesh->GetVertices();
				const auto& indices = mesh->GetIndexes();

				for (size_t i = 0; i < indices.size(); i += 3)
				{
					glm::vec3 v0 = vertices[indices[i]].Position;
					glm::vec3 v1 = vertices[indices[i + 1]].Position;
					glm::vec3 v2 = vertices[indices[i + 2]].Position;

					Plane* plane = new Plane(v0, v1, v2); // Suponiendo que `Plane` tiene un constructor con 3 puntos.
					Managers::BSPManager::AddPlane(plane);
				}
			}

			for (Entities::Entity* childModel : model->GetChildren())
			{
				RegisterModelPlanes(dynamic_cast<Entities::Model*>(childModel));
			}
		}

		void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, Entities::Entity* parentEntity, bool& createdMaterial)
		{
			Entities::Model* currentEntity = new Entities::Model(node->mName.C_Str());

			if (parentEntity)
			{
				currentEntity->SetParent(parentEntity);
			}

			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				currentEntity->SetBoundingBox(
					mesh->mAABB.mMin.x,
					mesh->mAABB.mMin.y,
					mesh->mAABB.mMin.z,
					mesh->mAABB.mMax.x,
					mesh->mAABB.mMax.y,
					mesh->mAABB.mMax.z
				);
				currentEntity->AddMesh(ProcessMesh(mesh, scene, currentEntity, createdMaterial));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene, currentEntity, createdMaterial);
			}
		}

		Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, Entities::Model* model, bool& createdMaterial)
		{
			std::vector<Entities::Vertex> vertices;
			std::vector<unsigned int> indices;
			//std::vector<Texture> textures;

			bool alreadyCreatedTexture = false;

			// walk through each of the mesh's vertices
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Entities::Vertex vertex;
				glm::vec3 vector;

				// positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;
				// normals
				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
					vertex.Normal = vector;
				}
				// texture coordinates
				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;

					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = vec;
					// tangent
					if (mesh->mTangents != nullptr)
					{
						vector.x = mesh->mTangents[i].x;
						vector.y = mesh->mTangents[i].y;
						vector.z = mesh->mTangents[i].z;
						vertex.Tangent = vector;
					}
					// bitangent
					if (mesh->mBitangents != nullptr)
					{
						vector.x = mesh->mBitangents[i].x;
						vector.y = mesh->mBitangents[i].y;
						vector.z = mesh->mBitangents[i].z;
						vertex.Bitangent = vector;
					}
				}
				else
					vertex.TexCoords = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];

				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			// process materials
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


			if (mesh->mMaterialIndex > 0 && !createdMaterial) //Si el modelo reconoce que hay materiales
			{
				std::string path = model->GetRoot()->GetDirectory();
				std::vector<std::string> order;
				std::string type;

				std::string matName = model->GetRoot()->GetName() + "_mat";
				Managers::MaterialManager::CreateMaterial(matName, Managers::ShaderManager::GetDefaultModelShader());
				Materials::Material* mat = Managers::MaterialManager::GetMaterial(matName);

				bool changed = false;

				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					type = "diffuse";
					if (mat->GetTexture(type) == -1)
					{
						std::string txName = model->GetRoot()->GetName() + "_" + type;
						Managers::TextureManager::CreateSearchedTexture(&(path)[0], &type[0], txName, true);
						mat->AddTexture(type, Managers::TextureManager::GetTextureID(txName));
						changed = true;
					}
					else
					{
						alreadyCreatedTexture = true;
					}
					order.push_back(type);
				}

				if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
				{
					type = "specular";
					if (mat->GetTexture(type) == -1)
					{
						std::string txName = model->GetRoot()->GetName() + "_" + type;
						Managers::TextureManager::CreateSearchedTexture(&(path)[0], &type[0], txName, true);
						mat->AddTexture(type, Managers::TextureManager::GetTextureID(txName));
						changed = true;
					}
					else
					{
						alreadyCreatedTexture = true;
					}
					order.push_back(type);
				}

				if (material->GetTextureCount(aiTextureType_HEIGHT) > 0)
				{
					type = "normal";
					if (mat->GetTexture(type) == -1)
					{
						std::string txName = model->GetRoot()->GetName() + "_" + type;
						Managers::TextureManager::CreateSearchedTexture(&(path)[0], &type[0], txName, true);
						mat->AddTexture(type, Managers::TextureManager::GetTextureID(txName));
						changed = true;
					}
					else
					{
						alreadyCreatedTexture = true;
					}
					order.push_back(type);
				}

				if (material->GetTextureCount(aiTextureType_AMBIENT) > 0)
				{
					type = "height";
					if (mat->GetTexture(type) == -1)
					{
						std::string txName = model->GetRoot()->GetName() + "_" + type;
						Managers::TextureManager::CreateSearchedTexture(&(path)[0], &type[0], txName, true);
						mat->AddTexture(type, Managers::TextureManager::GetTextureID(txName));
						changed = true;
					}
					else
					{
						alreadyCreatedTexture = true;
					}
					order.push_back(type);
				}

				if (changed)
				{
					mat->SetTextureOrder(order);
					Managers::MaterialManager::SetMaterial(matName, mat);
					createdMaterial = true;

					return new Mesh(vertices, indices);
				}
				else
				{
					Managers::MaterialManager::EraseMaterial(matName);
				}
				if (alreadyCreatedTexture)
				{
					return new Mesh(vertices, indices);
				}
			}

			return new Mesh(vertices, indices);

		}

		std::vector<Texture> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Entities::Model* model)
		{
			std::vector<Texture> textures;
			return textures;
		}
	}
}