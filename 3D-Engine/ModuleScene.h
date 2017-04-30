#ifndef _MODULE_SCENE_H
#define _MODULE_SCENE_H

#include <string>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "ModuleTextures.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Shader.h"
#pragma comment(lib, "assimp/lib/assimp.lib")

class ModuleScene
{
public:
	GameObject* root;
	std::vector<GameObject*> gameObjects;
	std::string directory;
	Shader shader;

	ModuleScene()
	{
		
	}

	~ModuleScene()
	{
		Clear();
	}

	Shader GetShader() 
	{
		return shader = Shader("../ModelShader.vs", "../ModelShader.fs");
	}

	GameObject* CreateGameObject(std::string path) // return game object
	{
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return nullptr;
		}
		// Retrieve the directory path of the filepath
		this->directory = path.substr(0, path.find_last_of('/'));

		// Process ASSIMP's root node recursively
		return  this->CreateNodes(scene->mRootNode, scene, nullptr);

	}


	GameObject* CreateNodes(aiNode* node, const aiScene* scene, GameObject* parent)
	{
		GameObject * newNode = new GameObject(node, scene, this->directory);
		newNode->parent = parent;
		newNode->shader = GetShader();
		gameObjects.push_back(newNode);

		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			GameObject* newChild = this->CreateNodes(node->mChildren[i], scene, newNode);
			newNode->addChild(newChild);

		}
		return newNode;
	}

	void Clear()
	{
		//falta agregar que se llame el metodo DeleteMeshBuffers
		for (int i = 0; i < gameObjects.size(); i++)
		{
			delete gameObjects[i];
		}
		gameObjects.clear();
	}

	GameObject* GetRootNode()
	{
		return root;
	}

	GameObject* FindNode(const char* name)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (strcmp(gameObjects[i]->name.c_str(), name)) {
				return gameObjects[i];
			}
		}
		return nullptr;
	}

	void LinkNode(GameObject* node, GameObject* destination)
	{
		node->parent->RemoveNode(node);
		destination->addChild(node);
	}

	void Update() 
	{
		for (int i = 0; i < gameObjects.size(); i++) 
		{
			gameObjects[i]->Update();
		}
	}
};

#endif // _MODULE_SCENE_H

