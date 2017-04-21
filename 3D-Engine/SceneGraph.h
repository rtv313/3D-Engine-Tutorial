#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H
#include <string>
#include <iostream>
#include <vector>
#include "GraphNode.h"
#include "ModuleTextures.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma comment(lib, "assimp/lib/assimp.lib")

class SceneGraph 
{
public:
	Camera camera;
	GraphNode* root;
	std::vector<GraphNode*> nodes;
	std::string directory;
	Shader shader;
	SceneGraph(GLchar* path)
	{
		this->Load(path);
		shader = Shader("../ModelShader.vs", "../ModelShader.fs");
	}

	~SceneGraph() 
	{
		Clear();
	}

	void Load(std::string path)
	{
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		// Retrieve the directory path of the filepath
		this->directory = path.substr(0, path.find_last_of('/'));

		// Process ASSIMP's root node recursively
		root = this->CreateNodes(scene->mRootNode, scene, nullptr);
		
	}


	GraphNode* CreateNodes(aiNode* node, const aiScene* scene, GraphNode* parent)
	{
		GraphNode * newNode = new GraphNode(node,scene,this->directory);
		newNode->parent = parent;
		nodes.push_back(newNode);

		for(GLuint i = 0; i < node->mNumChildren; i++)
		{
			GraphNode* newChild = this->CreateNodes(node->mChildren[i], scene, newNode);
			newNode->addChild(newChild);
			
		}
		
		return newNode;
	}

	
	

	void Clear() 
	{
		 //falta agregar que se llame el metodo DeleteMeshBuffers
		for (int i = 0; i < nodes.size(); i++) 
		{
			delete nodes[i];
		}
		nodes.clear();
	}


	void Draw() 
	{
		camera.do_movement();
		camera.mouse_movement();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // z-finding

		shader.Use();
		this->nodes;

		glm::mat4 projection = camera.getProjectionMatrix();
		glm::mat4 view = camera.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model;
		aiVector3D position = aiVector3D(0, 0, 0);
		aiVector3D scale = aiVector3D(1.0, 1.0, 1.0);
		aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
		aiMatrix4x4 m(scale, rotation, position);
		root->Draw(shader, m);
		
	}

	GraphNode* GetRootNode() 
	{
		return root;
	}

	GraphNode* FindNode(const char* name) 
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (strcmp(nodes[i]->name.c_str(), name)) {
				return nodes[i];
			}
		}

		return nullptr;
	}

	void LinkNode(GraphNode* node, GraphNode* destination) 
	{
		node->parent->RemoveNode(node);
		destination->addChild(node);
	}
};
#endif // !SCENE_GRAPH_H
