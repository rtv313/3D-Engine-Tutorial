#include "ComponentTransform.h"
#include "GameObject.h";
#include "glm/gtc/matrix_transform.hpp"

ComponentTransform::ComponentTransform(GameObject * go) :Component(go) 
{
	type = TRANSFORM;
}

update_status ComponentTransform::Update() 
{
	UpdateTransforms();
	return UPDATE_CONTINUE;
}

void ComponentTransform::UpdateTransforms() 
{

	rotation = aiQuaternion(1, 0, 0, 0);
	aiQuaternion rotX = aiQuaternion(aiVector3D(1.0, 0.0, 0.0), glm::radians(rotationDegrees.x));
	aiQuaternion rotY = aiQuaternion(aiVector3D(0.0, 1.0, 0.0), glm::radians(rotationDegrees.y));
	aiQuaternion rotZ = aiQuaternion(aiVector3D(0.0, 0.0, 1.0), glm::radians(rotationDegrees.z));

	rotation = rotation*rotX;
	rotation = rotation*rotY;
	rotation = rotation*rotZ;

	if (my_go->parent == nullptr)
	{
		this->worldTransform = aiMatrix4x4(scale, rotation, position) * aiMatrix4x4(aiVector3D(1, 1, 1), aiQuaternion(1, 0, 0, 0), aiVector3D(0, 0, 0));
	}
	else
	{
		this->worldTransform = aiMatrix4x4(scale, rotation, position) * my_go->parent->transform->worldTransform;
	}
}