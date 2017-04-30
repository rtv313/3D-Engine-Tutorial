#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "Glew/include/GL/glew.h"

GameObject::GameObject(aiNode* node, const aiScene* scene, std::string directory)
{
	transform = new ComponentTransform(this);
	this->directory = directory;
	this->name = node->mName.C_Str();
	
	ComponentMesh * meshComponent = new ComponentMesh(node,scene,this);
	components.push_back(meshComponent);
}

GameObject::~GameObject() 
{
	this->name;
	this->childs;
	delete transform;
	for (int i = 0; i < components.size(); i++) 
	{
		delete components[i];
	}
	components.clear();
	
	childs.clear();
}

void GameObject::addChild(GameObject * child)
{
	childs.push_back(child);
}

void GameObject::RemoveNode(GameObject * childToRemove)
{
	for (int i = 0; i < childs.size(); i++)
	{
		if (childs[i] == childToRemove)
		{
			childs.erase(childs.begin() + i);
			return;
		}
	}
	return;
}

void GameObject::Update() 
{
	this->transform->Update();
	for (int i = 0; i < components.size(); i++) 
	{
		components[i]->Update();
	}
}

