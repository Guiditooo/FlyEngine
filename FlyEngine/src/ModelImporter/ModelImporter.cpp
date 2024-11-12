#include "ModelImporter.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "MaterialManager/MaterialManager.h"
#include "ShaderManager/ShaderManager.h"

#include "TextureImporter/TextureImporter.h"
#include "Texture/Texture.h"
#include "Mesh/Mesh.h"
#include "Model/Model.h"
#include "Vertex/Vertex.h"
//#include "Materi"

namespace FlyEngine
{
	namespace Importers
	{
		Entities::Model* ModelImporter::LoadModel(std::string modelName, std::string const& path, bool gamma)
		{
			Entities::Model* model = new Entities::Model(modelName);

			// read file via ASSIMP
			Assimp::Importer importer;

			//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

			const aiScene* scene = importer.ReadFile(path,
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType |
				aiProcess_FlipUVs |
				aiProcess_CalcTangentSpace |
				aiProcess_GenSmoothNormals |
				aiProcess_LimitBoneWeights);

			// check for errors
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return nullptr;
			}

			// retrieve the directory path of the filepath
			model->SetDirectory(path.substr(0, path.find_last_of('/')) + "/");

			// process ASSIMP's root node recursively
			ProcessNode(scene->mRootNode, scene, model);
			return model;
		}
		void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, Entities::Model* model)
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				// the node object only contains indices to index the actual objects in the scene. 
				// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				model->AddMesh(ProcessMesh(mesh, scene, model));
			}
			// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene, model);
			}
		}

		Entities::Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, Entities::Model* model)
		{
			std::vector<Entities::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			bool alreadyCreatedTexture = false;

			// walk through each of the mesh's vertices
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Entities::Vertex vertex;
				glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
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
					// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
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
			// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			// process materials
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// diffuse: texture_diffuseN
			// specular: texture_specularN
			// normal: texture_normalN


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


			// return a mesh object created from the extracted mesh data
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