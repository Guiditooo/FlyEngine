#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Exports/Exports.h>
#include <Material/Material.h>
#include <FlyFunctions/Color/Color.h>


class Entity
{
protected:

	unsigned int VBO; //Vertex Buffer Object
	unsigned int VAO; //Vertex Array Object
	unsigned int EBO; //Elements Buffer Object

	//float vertices[2];
	int drawLayer;
	bool active;

	Material* material;

	glm::mat4 model;

	FLY_ENGINE::Color color;

	glm::mat4 translateMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::quat rotationQuaternion;
	glm::vec3 scaleVector;

	glm::quat EulerToQuat(glm::vec3 euler);
	glm::mat4 EulerToMat4(glm::vec3 euler);
	glm::vec3 QuaternionToEuler(glm::quat quat);
	glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
	glm::quat QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards);

	
public:
	Entity();
	~Entity();

	void SetActive(bool isActive);
	bool IsActive();

	void SetDrawLayer(int newDrawLayer);
	int GetDrawLayer();

	void SetColor(FLY_ENGINE::Color newColor);
	void SetColor(glm::vec3 newColor);
	void SetColor(float r, float g, float b);
	void SetColor(FLY_ENGINE::COLOR newColor);

	void UpdateModelMatrix();
	glm::mat4 GetModelMatrix();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	void SetMaterial(Material* newMaterial);
	Material* GetMaterial();

	virtual void Draw() = 0;
};

#endif // !ENTITY_H