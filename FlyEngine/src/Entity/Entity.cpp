#include "Entity.h"

#include <string>
#include <glm/gtx/euler_angles.hpp>

#include "Renderer/Renderer.h"
#include "Material/Material.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include "MaterialManager/MaterialManager.h"

#include "Mesh/Mesh.h"

namespace FlyEngine
{
	namespace Entities
	{

		Entity::Entity(std::string name, Entity* parent)
		{
			CreateBaseEntity(name);
			SetParent(parent);
		}
		Entity::Entity(std::string name, glm::vec3 pos, Entity* parent)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetParent(parent);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, Entity* parent)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
			SetParent(parent);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale, Entity* parent)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
			SetScale(scale.x, scale.y, scale.z);
			SetParent(parent);
		}

		void Entity::CreateBaseEntity(std::string name)
		{
			this->name = name;

			indexCount = 0;
			vertexCount = 0;
			vertexSize = 0;

			material = Managers::MaterialManager::GetDefaultMissingMaterial();
			buffers = new Utils::Buffers();
			active = true;

			printModificationMessage = false;

			transform = new Transform();
		}

		Entity::~Entity()
		{
		}

		void Entity::SetActive(bool isActive)
		{
			active = isActive;

			for (auto element : children)
			{
				element->SetActive(isActive);
			}
		}

		bool Entity::IsActive()
		{
			return active;
		}

		void Entity::SetAsCameraTarget(bool value)
		{
			settedAsCameraTarget = value;
		}

		bool Entity::IsCameraTarget()
		{
			return settedAsCameraTarget;
		}

		void Entity::SetName(std::string newName)
		{
			name = newName;
		}

		void Entity::PrintCreationMsg()
		{
			std::string text = "Created ";
			text += name;
			text += " successfully!";

			Debugger::ConsoleMessageID(&text[0]);
		}

		void Entity::SetColor(FlyEngine::Color newColor)
		{
			color = newColor;
		}

		void Entity::SetColor(glm::vec3 newColor)
		{
			color = Color(newColor);
		}

		void Entity::SetColor(float r, float g, float b)
		{
			color = Color(r, g, b);
		}

		void Entity::SetColor(FlyEngine::COLOR newColor)
		{
			color = newColor;
		}

		Utils::Color Entity::GetColor()
		{
			return material->GetColor();
		}

		glm::vec3 Entity::GetColorV3()
		{
			return color.GetColorV3();
		}

		glm::mat4 Entity::GetModelMatrix()
		{
			return transform->GetModelMatrix();
		}

		std::vector<Mesh*> Entity::GetSubMeshes()
		{
			return std::vector<Mesh*>();
		}

		void Entity::SetPosition(float x, float y, float z)
		{
			transform->SetPosition(x, y, z);

			if (printModificationMessage)
			{
				std::string text = "Setted Position of ";
				text += name;
				text += " successfully to: ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}

		}

		void Entity::SetPosition(float x)
		{
			SetPosition(x, x, x);
		}

		void Entity::SetPosition(glm::vec3 pos)
		{
			SetPosition(pos.x, pos.y, pos.z);
		}

		void Entity::SetRotation(float x, float y, float z)
		{
			transform->SetRotation(x, y, z);

			if (printModificationMessage)
			{
				std::string text = "Setted Rotation of ";
				text += name;
				text += " successfully to: ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}
		}

		void Entity::SetRotation(glm::vec3 rot)
		{
			SetRotation(rot.x, rot.y, rot.z);
		}

		void Entity::SetRotation(glm::quat rot)
		{
			transform->SetRotation(rot);

			if (printModificationMessage)
			{
				std::string text = "Setted Rotation of ";
				text += name;
				text += " successfully to: ";

				glm::vec3 rot = transform->GetRotation();

				Debugger::ConsoleMessageID(&text[0], glm::vec3(rot.x, rot.y, rot.z));
			}
		}

		void Entity::SetScale(float x, float y, float z)
		{
			transform->SetScale(x, y, z);

			if (printModificationMessage)
			{
				std::string text = "Setted Scale of ";
				text += name;
				text += ". Now its ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}
		}

		void Entity::SetScale(glm::vec3 scale)
		{
			SetScale(scale.x, scale.y, scale.z);
		}

		void Entity::SetScale(float scale)
		{
			SetScale(scale, scale, scale);
		}

		void Entity::SetBoundingBox(Utils::BoundingBox bounds)
		{
			boundingBox = bounds;

			if (parent != nullptr)
			{
				Utils::BoundingBox pbb = parent->GetBoundingBox();

				pbb.min.x = bounds.min.x < pbb.min.x ? bounds.min.x : pbb.min.x;
				pbb.min.y = bounds.min.y < pbb.min.y ? bounds.min.y : pbb.min.y;
				pbb.min.z = bounds.min.z < pbb.min.z ? bounds.min.z : pbb.min.z;

				pbb.max.x = bounds.max.x > pbb.max.x ? bounds.max.x : pbb.max.x;
				pbb.max.y = bounds.max.y > pbb.max.y ? bounds.max.y : pbb.max.y;
				pbb.max.z = bounds.max.z > pbb.max.z ? bounds.max.z : pbb.max.z;

				parent->SetBoundingBox(pbb);
			}
		}

		void Entity::SetBoundingBox(glm::vec3 min, glm::vec3 max)
		{
			boundingBox.min = min;
			boundingBox.max = max;

			if (parent != nullptr)
			{
				Utils::BoundingBox pbb = parent->GetBoundingBox();

				pbb.min.x = min.x < pbb.min.x ? min.x : pbb.min.x;
				pbb.min.y = min.y < pbb.min.y ? min.y : pbb.min.y;
				pbb.min.z = min.z < pbb.min.z ? min.z : pbb.min.z;

				pbb.max.x = max.x > pbb.max.x ? max.x : pbb.max.x;
				pbb.max.y = max.y > pbb.max.y ? max.y : pbb.max.y;
				pbb.max.z = max.z > pbb.max.z ? max.z : pbb.max.z;

				parent->SetBoundingBox(pbb);
			}
		}

		void Entity::SetBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
		{
			boundingBox.min.x = minX;
			boundingBox.min.y = minY;
			boundingBox.min.z = minZ;
			boundingBox.max.x = maxX;
			boundingBox.max.y = maxY;
			boundingBox.max.z = maxZ;

			if (parent != nullptr)
			{
				Utils::BoundingBox pbb = parent->GetBoundingBox();

				pbb.min.x = minX < pbb.min.x ? minX : pbb.min.x;
				pbb.min.y = minY < pbb.min.y ? minY : pbb.min.y;
				pbb.min.z = minZ < pbb.min.z ? minZ : pbb.min.z;

				pbb.max.x = maxX > pbb.max.x ? maxX : pbb.max.x;
				pbb.max.y = maxY > pbb.max.y ? maxY : pbb.max.y;
				pbb.max.z = maxZ > pbb.max.z ? maxZ : pbb.max.z;

				parent->SetBoundingBox(pbb);
			}
		}

		Utils::BoundingBox Entity::GetBoundingBox()
		{
			return boundingBox;
		}

		void Entity::AddChild(Entity* newChild)
		{
			children.push_back(newChild);
			if (newChild->GetParent() != this)
			{
				newChild->SetParent(this);
			}
		}

		void Entity::SetParent(Entity* newParent)
		{
			parent = newParent;
			if (newParent)
				newParent->AddChild(this);
		}

		void Entity::RemoveChild(Entity* child)
		{
			auto it = std::find(children.begin(), children.end(), child);
			if (it != children.end())
			{
				children.erase(it);
				child->RemoveParent();
			}
		}

		void Entity::RemoveParent()
		{
			parent = nullptr;
		}

		void Entity::Traverse(const std::function<void(Entity*)>& action)
		{
			action(this);

			//ACA NO FALTA ALGO?

			for (Entity* child : children)
			{
				child->Traverse(action);
			}
		}

		Transform* Entity::GetTransform()
		{
			return transform;
		}

		glm::mat4 Entity::GetWorldTransform()
		{
			// Si la entidad tiene un padre, multiplica su transformación local con la global del padre
			if (parent != nullptr)
			{
				return parent->GetWorldTransform() * transform->GetModelMatrix();
			}
			// Si no tiene un padre, su transformación global es igual a su transformación local
			return transform->GetModelMatrix();
		}

		Entity* Entity::GetParent()
		{
			return parent;
		}

		std::vector<Entity*> Entity::GetChilds()
		{
			return children;
		}

		void Entity::SetMaterial(Materials::Material* newMaterial, bool setRecursively)
		{
			material = newMaterial;

			std::vector<Entities::Mesh*> subMeshes = GetSubMeshes();

			for (auto subMesh : subMeshes)
			{
				subMesh->SetMaterial(newMaterial, false);
			}

			if (setRecursively)
			{
				for (auto element : children)
				{
					element->SetMaterial(newMaterial, setRecursively);
				}
			}
		}

		Materials::Material* Entity::GetMaterial()
		{
			return material;
		}

		Shader* Entity::GetShader()
		{
			return material->GetShader();
		}

		int Entity::GetShaderID()
		{
			return material->GetShader()->GetShaderID();
		}

		FlyEngine::Utils::Buffers* Entity::GetBuffers()
		{
			return buffers;
		}

		int Entity::GetIndexCount()
		{
			return indexCount;
		}

		std::vector<VertexAttribute> Entity::GetVertexAttributes()
		{
			return vertexAttributes;
		}

		std::vector<float> Entity::GetVertexList()
		{
			return vertex;
		}

		std::vector<unsigned int> Entity::GetIndexList()
		{
			return index;
		}

		void Entity::MoveForward(float amount)
		{
			glm::vec3 forward = transform->GetFront();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += forward * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::MoveBackward(float amount)
		{
			glm::vec3 backward = -transform->GetFront();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += backward * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::MoveLeft(float amount)
		{
			glm::vec3 left = -transform->GetRight();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += left * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::MoveRight(float amount)
		{
			glm::vec3 right = transform->GetRight();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += right * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::MoveUp(float amount)
		{
			glm::vec3 up = transform->GetUp();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += up * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::MoveDown(float amount)
		{
			glm::vec3 down = -transform->GetUp();
			glm::vec3 currentPosition = transform->GetPosition();
			currentPosition += down * amount;
			SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		}

		void Entity::ToggleModificationMessage(bool isActive)
		{
			printModificationMessage = isActive;
		}

		void Entity::UseShader()
		{
			material->GetShader()->UseShader();
		}

		int Entity::GetVertexCount()
		{
			return vertexCount;
		}

		int Entity::GetVertexSize()
		{
			return vertexSize;
		}

		std::string Entity::GetName()
		{
			return name;
		}

	}

}