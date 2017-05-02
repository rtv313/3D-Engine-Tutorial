#include "ComponentTransform.h"
#include "GameObject.h";

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
	if (my_go->parent == nullptr)
	{
		this->worldTransform = aiMatrix4x4(scale, rotation, position) * aiMatrix4x4(aiVector3D(1, 1, 1), aiQuaternion(1, 0, 0, 0), aiVector3D(0, 0, 0));
	}
	else
	{
		this->worldTransform = aiMatrix4x4(scale, rotation, position) * my_go->parent->transform->worldTransform;
	}
}