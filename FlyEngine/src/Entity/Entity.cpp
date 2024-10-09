#include "Entity.h"

#include <string>
#include <glm/gtx/euler_angles.hpp>

#include "Renderer/Renderer.h"
#include "Material/Material.h"
#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	namespace Entities
	{

		Entity::Entity(std::string name)
		{
			CreateBaseEntity(name);
		}
		Entity::Entity(std::string name, glm::vec3 pos)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
			SetScale(scale.x, scale.y, scale.z);
		}

		void Entity::CreateBaseEntity(std::string name)
		{
			this->name = name;

			color = glm::vec3(1.0f);

			indexCount = 0;
			vertexCount = 0;
			vertexSize = 0;

			material = nullptr;
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
			std::string text = name;

			active = isActive;

			text += active ? " is Active!" : " is not Active!";

			Debugger::ConsoleMessage(&text[0]);
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
			color = Color(newColor);
		}

		Utils::Color Entity::GetColor()
		{
			return color;
		}

		glm::mat4 Entity::GetModelMatrix()
		{
			return transform->GetModelMatrix();
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
			transform->SetScale(x,y,z);

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

		Transform* Entity::GetTransform()
		{
			return transform;
		}

		

		void Entity::SetMaterial(Materials::Material* newMaterial)
		{
			material = newMaterial;
			std::string text = "Material ["+ newMaterial->GetName() + "] added to " + name + "!";
			Debugger::ConsoleMessage(&text[0],1,0,0,1);
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

		void Entity::Draw()
		{
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