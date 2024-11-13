#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include "Exports/Exports.h"
#include "assimp/scene.h"

#include "Model/Model.h"

namespace FlyEngine
{
	class Texture;

	namespace Importers
	{
		class FLY_API ModelImporter
		{
		public:
			static Entities::Model* LoadModel(std::string modelName, std::string const& path, bool gamma = false);
		private:
			static void ProcessNode(aiNode* node, const aiScene* scene, Entities::Model* model);
			static Entities::Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, Entities::Model* model);
			static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Entities::Model* model);
			
		
		};

	}

}
#endif // !MODEL_IMPORTER_H