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

			void UpdateMeshesTransform();
		public:
			Model(std::string modelName = "GenericModelName", bool gamma = false);

			void SetDirectory(std::string directory);
			void AddMesh(Mesh* mesh);

			glm::vec3 GetDimesions();
			std::vector<Mesh*> GetMeshes();
			std::string GetDirectory();

			void SetPosition(float x, float y, float z) override;
			void SetPosition(float x) override;
			void SetPosition(glm::vec3 pos) override;

			void SetRotation(float x, float y, float z) override;
			void SetRotation(glm::vec3 rot) override;
			void SetRotation(glm::quat rot) override;

			void SetScale(float x, float y, float z) override;
			void SetScale(glm::vec3 scale) override;
			void SetScale(float scale) override;

			void Translate(float x, float y, float z);
			void Translate(glm::vec3 pos);

			void Rotate(float x, float y, float z);
			void Rotate(glm::vec3 rot);

			void Scale(float x, float y, float z);
			void Scale(glm::vec3 scale);
			void Scale(float scale);

			//void SetColor(Utils::Color newColor) override;
			//void SetColor(glm::vec3 newColor) override;
			//void SetColor(float r, float g, float b) override;
			//void SetColor(Utils::COLOR newColor) override;

			void UseBaseMaterial(bool useBaseMat);
			bool ShouldUseBaseMaterial();

			std::vector<Mesh*> GetSubMeshes() override;
		};
	}
}

#endif // !MODEL_H