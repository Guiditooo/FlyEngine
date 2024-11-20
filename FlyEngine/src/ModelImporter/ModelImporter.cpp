#include "ModelImporter.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "MaterialManager/MaterialManager.h"
#include "ShaderManager/ShaderManager.h"
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
		std::vector<Entities::Model*> ModelImporter::LoadModel(std::string modelName, std::string const& path, bool gamma)
		{
			std::vector<Entities::Model*> modelVector;

			Entities::Model* model = new Entities::Model(modelName);

			modelVector.push_back(model);

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

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return modelVector;
			}

			model->SetDirectory(path.substr(0, path.find_last_of('/')) + "/");

			ProcessNode(scene->mRootNode, scene, model, modelVector);
			return modelVector;
		}

		Entities::Model* ModelImporter::LoadBSPScene(std::string modelName, std::string const& path, bool gamma)
		{
			return nullptr;
		}
		void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, Entities::Entity* parentEntity, std::vector<Entities::Model*>& modelVector)
		{
			Entities::Model* currentEntity = new Entities::Model(node->mName.C_Str());
			
			modelVector.push_back(currentEntity);

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
				currentEntity->AddMesh(ProcessMesh(mesh, scene, currentEntity));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++) 
			{
				ProcessNode(node->mChildren[i], scene, currentEntity, modelVector);
			}
		}

		Entities::Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, Entities::Model* model)
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


			if (mesh->mMaterialIndex > 0) //Si el modelo reconoce que hay materiales
			{
				std::string path = model->GetDirectory();
				std::vector<std::string> order;
				std::string type;

				std::string matName = model->GetName() + "_mat";
				Managers::MaterialManager::CreateMaterial(matName, Managers::ShaderManager::GetDefaultModelShader());
				Materials::Material* mat = Managers::MaterialManager::GetMaterial(matName);

				bool changed = false;

				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					type = "diffuse";
					if (mat->GetTexture(type) == -1)
					{
						mat->AddTexture(type, TextureImporter::SearchTexture(&(path)[0], &type[0])->GetID());
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
						mat->AddTexture(type, TextureImporter::SearchTexture(&(path)[0], &type[0])->GetID());
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
						mat->AddTexture(type, TextureImporter::SearchTexture(&(path)[0], &type[0])->GetID());
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
						mat->AddTexture(type, TextureImporter::SearchTexture(&(path)[0], &type[0])->GetID());
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
					return new Entities::Mesh(vertices, indices, mat);
				}
				if (alreadyCreatedTexture)
				{
					return new Entities::Mesh(vertices, indices, mat);
				}
			}

			return new Entities::Mesh(vertices, indices, Managers::MaterialManager::GetDefaultModelMaterial());

		}

		std::vector<Texture> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Entities::Model* model)
		{
			std::vector<Texture> textures;
			/*
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
				bool skip = false;
				for (unsigned int j = 0; j < model->textures_loaded.size(); j++)
				{
					if (std::strcmp(model->textures_loaded[j].path.data(), str.C_Str()) == 0)
					{
						textures.push_back(model->textures_loaded[j]);
						skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
						break;
					}
				}
				if (!skip)
				{   // if texture hasn't been loaded already, load it
					Texture texture;
					texture.id = Importers::TextureImporter::TextureFromFile(str.C_Str(), model->directory);
					texture.type = typeName;
					texture.path = str.C_Str();
					textures.push_back(texture);
					model->textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
				}
			}
			*/
			return textures;
		}
	}
}