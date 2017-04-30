#ifndef COMPONENT_TRANSFORM_H
#define COMPONENT_TRANSFORM_H

#include"Component.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ComponentTransform :public Component
{
public:
	aiVector3D position = aiVector3D(0, 0, 0);
	aiVector3D scale = aiVector3D(1, 1, 1);
	aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
	aiMatrix4x4 worldTransform;
	update_status Update();
	ComponentTransform(GameObject* go);
private:
	void UpdateTransforms();
	
};
#endif // !COMPONENT_TRANSFORM_H

