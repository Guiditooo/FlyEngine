#ifndef MODEL_H
#define MODEL_H

#include "Entity3D/Entity3D.h"
#include "Mesh/Mesh.h"

namespace FlyEngine
{

	namespace Entities
	{
		class FLY_API Model : public Entity3D
		{
		private:
			std::vector<Mesh*> meshes;
			std::string directory;

			bool gammaCorrection;
			bool useBaseMaterial;
		public:
			Model(std::string modelName = "GenericModelName", bool gamma = false);

			void SetDirectory(std::string directory);
			void AddMesh(Mesh* mesh);

			glm::vec3 GetDimesions();
			std::vector<Mesh*> GetMeshes();
			std::string GetDirectory();

			void UseBaseMaterial(bool useBaseMat);
			bool ShouldUseBaseMaterial();
		};
	}
}

#endif // !MODEL_H