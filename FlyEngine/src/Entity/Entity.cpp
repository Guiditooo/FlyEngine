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
			transform = new Transform();
			CreateBaseEntity(name);
			if(parent)
				SetParent(parent);
		}

		Entity::Entity(std::string name, glm::vec3 pos, Entity* parent)
		{
			transform = new Transform();
			CreateBaseEntity(name);
			transform->SetWorldPosition(pos.x, pos.y, pos.z);
			if (parent)
				SetParent(parent);
		}

		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, Entity* parent)
		{
			transform = new Transform();
			CreateBaseEntity(name);
			transform->SetWorldPosition(pos.x, pos.y, pos.z);
			transform->SetWorldRotation(rot);
			if (parent)
				SetParent(parent);
		}

		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale, Entity* parent)
		{
			transform = new Transform();
			CreateBaseEntity(name);
			transform->SetWorldPosition(pos.x, pos.y, pos.z);
			transform->SetWorldRotation(rot);
			transform->SetWorldScale(scale.x, scale.y, scale.z);

			if(parent)
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

			transform->SetEntity(this);

			localBoundingBox = Utils::BoundingBox();
			worldBoundingBox = Utils::BoundingBox();

		}

		Entity::~Entity()
		{
		}

		void Entity::SetActive(bool isActive)
		{
			activeInHierarchy = active;
			active = isActive;
			for (auto child : transform->GetChildren())
			{
				if (!active)
				{
					child->GetEntity()->SetActive(isActive);
				}
				else
				{
					child->GetEntity()->SetActive(activeInHierarchy);
				}
			}
		}

		bool Entity::IsActive()
		{
			return active;
		}

		bool Entity::IsActiveInHierarchy()
		{
			if (transform->GetParent() != nullptr)
				return transform->GetParent()->GetEntity()->IsActiveInHierarchy();
			
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
			return transform->GetWorldTRS();
		}


		/*
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
		*/

		void Entity::SetBoundingBox(Utils::BoundingBox bounds)
		{
			localBoundingBox = bounds;

			if (transform->GetParent() != nullptr)
			{
				Utils::BoundingBox pbb = transform->GetParent()->GetEntity()->GetLocalBoundingBox();

				pbb.min.x = bounds.min.x < pbb.min.x ? bounds.min.x : pbb.min.x;
				pbb.min.y = bounds.min.y < pbb.min.y ? bounds.min.y : pbb.min.y;
				pbb.min.z = bounds.min.z < pbb.min.z ? bounds.min.z : pbb.min.z;

				pbb.max.x = bounds.max.x > pbb.max.x ? bounds.max.x : pbb.max.x;
				pbb.max.y = bounds.max.y > pbb.max.y ? bounds.max.y : pbb.max.y;
				pbb.max.z = bounds.max.z > pbb.max.z ? bounds.max.z : pbb.max.z;

				transform->GetParent()->GetEntity()->SetBoundingBox(pbb);
			}
		}

		void Entity::SetBoundingBox(glm::vec3 min, glm::vec3 max)
		{
			SetBoundingBox(BoundingBox(min,max));
		}

		void Entity::SetBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
		{
			SetBoundingBox(BoundingBox(glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ)));
		}

		void Entity::SetWorldBoundingBox(Utils::BoundingBox bounds)
		{
			worldBoundingBox = bounds;
		}

		Utils::BoundingBox Entity::GetLocalBoundingBox()
		{
			return localBoundingBox;
		}

		Utils::BoundingBox Entity::GetWorldBoundingBox()
		{
			glm::mat4 worldTRS = transform->GetWorldTRS();
			worldBoundingBox = Utils::BoundingBox::TransformBoundingBox(localBoundingBox, worldTRS);
			return worldBoundingBox;
		}

		void Entity::AddChild(Entity* newChild)
		{
			transform->AddChild(newChild->GetTransform());
		}

		void Entity::SetParent(Entity* newParent)
		{
			transform->SetParent(newParent->GetTransform());
		}

		void Entity::RemoveChild(Entity* child)
		{
			transform->RemoveChild(child->GetTransform());
		}

		void Entity::RemoveParent()
		{
			transform->RemoveParent();
		}

		void Entity::Traverse(const std::function<void(Entity*)>& action)
		{
			action(this);

			//ACA NO FALTA ALGO?
			/*
			for (Entity* child : children)
			{
				child->Traverse(action);
			}
			*/
		}

		Transform* Entity::GetTransform()
		{
			return transform;
		}

		Entity* Entity::GetParent()
		{
			return transform->GetParent()->GetEntity();
		}

		Entity* Entity::GetRoot()
		{
			return transform->GetRoot()->GetEntity();
		}

		std::vector<Entity*> Entity::GetChildren()
		{
			std::vector<Entity*> ret;
			for (auto child : transform->GetChildren())
			{
				ret.push_back(child->GetEntity());
			}
			return ret;
		}

		std::vector<Entity*> Entity::GetChildrenWithName(std::string childName)
		{
			std::vector<Entity*> ret = std::vector<Entity*>();
			for (auto child : transform->GetChildrenWithName(childName))
			{
				ret.push_back(child->GetEntity());
			}
			return ret;
		}

		void Entity::SetMaterial(Materials::Material* newMaterial, bool setRecursively)
		{
			material = newMaterial;

			if (setRecursively)
			{
				for (auto element : transform->GetChildren())
				{
					element->GetEntity()->SetMaterial(newMaterial, setRecursively);
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
			glm::vec3 movement = forward * amount;
			transform->WorldTranslate(movement.x, movement.y, movement.z);
		}

		void Entity::MoveBackward(float amount)
		{
			MoveForward(-amount);
		}

		void Entity::MoveLeft(float amount)
		{
			MoveRight(-amount);
		}

		void Entity::MoveRight(float amount)
		{
			glm::vec3 right = transform->GetRight();
			glm::vec3 movement = right * amount;
			transform->WorldTranslate(movement.x, movement.y, movement.z);
		}

		void Entity::MoveUp(float amount)
		{
			glm::vec3 up = transform->GetUp();
			glm::vec3 movement = up * amount;
			transform->WorldTranslate(movement.x, movement.y, movement.z);
		}

		void Entity::MoveDown(float amount)
		{
			MoveUp(-amount);
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