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
#include "Grid.h"
#pragma comment(lib, "assimp/lib/assimp.lib")

class ModuleScene : public Module
{
public:
	
	std::vector<GameObject*> gameObjects;
	std::string directory;
	GameObject * root;
	
	ModuleScene();
	~ModuleScene();
	Shader GetShader();
	GameObject* CreateGameObject(std::string path);
	GameObject* CreateNodes(aiNode* node, const aiScene* scene, GameObject* parent);
	void Clear();
	GameObject* FindGameObject(const char* name);
	void LinkGameObject(GameObject* go, GameObject* destination);
	void UpdateGameObjects();
	update_status Update();
	bool Init();
	Grid *grid;
};

#endif // _MODULE_SCENE_H

