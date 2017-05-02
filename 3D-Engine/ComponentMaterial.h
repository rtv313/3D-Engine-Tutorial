#ifndef COMPONENT_MATERIAL_H
#define COMPONENT_MATERIAL_H
#include <string>
#include <map>
#include"Component.h"
#include "Shader.h"
#include "assimp/scene.h"

class Material 
{
public:
	unsigned int id;
	aiMaterial material;
	std::string name;
	aiColor3D colorDiffuse;
	aiColor3D colorSpecular;
	aiColor3D colorAmbient;
	aiColor3D colorEmissive;
	aiColor3D colorTransparent;
	float shininess=0.0f;
	float shininessStrength=0.0f;
	Shader shader;
};

class ComponentMaterial :public Component
{
public:
	std::map<int,Material*> materials;
	ComponentMaterial(GameObject* go);
	~ComponentMaterial();
	update_status Update();
};
#endif // COMPONENT_MATERIAL_H
