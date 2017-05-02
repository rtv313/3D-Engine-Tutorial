#ifndef COMPONENT_MESH_H
#define COMPONENT_MESH_H

#include <string>
#include "GraphMaterial.h"
#include "Glew/include/GL/glew.h"

#include "Shader.h"
#include "Component.h"
#include "GraphMesh.h"
#include <vector>
#pragma comment(lib, "assimp/lib/assimp.lib")



class ComponentMesh :public Component 
{
public:
	std::vector<GraphMesh> meshes;
	ComponentMesh(aiNode* node, const aiScene* scene,GameObject* go);
	~ComponentMesh();
	void ComponentDraw();
	void Clear();
	update_status Update();
	

private:
	void  CreateMeshes(aiNode* node, const aiScene* scene);
	GraphMesh  processMesh(aiMesh * mesh, const aiScene* scene);
	std::vector<TextureGraph> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	void CreateMaterials(aiNode* node, const aiScene* scene);
};

#endif // !COMPONENT_MESH:H

