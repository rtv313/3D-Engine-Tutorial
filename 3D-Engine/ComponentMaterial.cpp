#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(GameObject * go) :Component(go)
{
	type = MATERIAL;
}

ComponentMaterial::~ComponentMaterial()
{
	for (int i = 0; i < materials.size(); i++) 
	{
		delete materials[i];
	}

	materials.clear();
}


update_status ComponentMaterial::Update()
{
	
	return UPDATE_CONTINUE;
}


