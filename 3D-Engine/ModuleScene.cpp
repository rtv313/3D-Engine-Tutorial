#include "ModuleScene.h"
#include "Brofiler/Brofiler.h"

ModuleScene::ModuleScene() 
{
	root = new GameObject();
	root->name = "Scene Root";
}

ModuleScene::~ModuleScene() 
{
	delete root;
	delete grid;
	Clear();
}

Shader ModuleScene::GetShader() 
{
	return Shader("../ModelShader.vs", "../ModelShader.fs");
}

GameObject* ModuleScene::CreateGameObject(std::string path)
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
	root->childs.push_back (this->CreateNodes(scene->mRootNode, scene, nullptr));
	return root;
}

GameObject * ModuleScene::CreateNodes(aiNode* node, const aiScene* scene, GameObject* parent)
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

void ModuleScene::Clear() 
{
	//falta agregar que se llame el metodo DeleteMeshBuffers
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

GameObject * ModuleScene::FindGameObject(const char* name)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (strcmp(gameObjects[i]->name.c_str(), name)) {
			return gameObjects[i];
		}
	}
	return nullptr;
}

void ModuleScene::LinkGameObject(GameObject* go, GameObject* destination)
{
	go->parent->RemoveNode(go);
	destination->addChild(go);
}

void ModuleScene::UpdateGameObjects()
{
	
}

update_status ModuleScene::Update() 
{
	BROFILER_CATEGORY("Module Scene",Profiler::Color::Lime);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // z-finding

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}

	grid->Draw();
	glDisable(GL_DEPTH_TEST);

	return UPDATE_CONTINUE;
}

bool ModuleScene::Init() 
{
	//CreateGameObject("../Models/street/Street.obj");
	CreateGameObject("../Models/Nanosuit/nanosuit.obj");
	grid = new Grid();
	return true;
}