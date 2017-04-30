#include "ComponentMesh.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleCameraEditor.h"
#include "glm/gtc/type_ptr.hpp"

ComponentMesh::ComponentMesh(aiNode* node, const aiScene* scene, GameObject* go):Component(go)
{
	CreateMeshes(node, scene);
}

ComponentMesh::~ComponentMesh() 
{
	Clear();
	meshes.clear();
}


void ComponentMesh::Clear() 
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].DeleteMeshBuffers();
	}

	meshes.clear();
}

void ComponentMesh::CreateMeshes(aiNode* node, const aiScene* scene) 
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
}

GraphMesh  ComponentMesh::processMesh(aiMesh * mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<VertexGraph> vertices;
	std::vector<GLuint> indices;
	std::vector<TextureGraph> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		VertexGraph vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// 1. Diffuse maps
		std::vector<TextureGraph> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<TextureGraph> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return GraphMesh(vertices, indices, textures);
}

std::vector<TextureGraph> ComponentMesh::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) 
{
	std::vector<TextureGraph> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		TextureGraph texture;
		std::string fullPath = this->my_go->directory + "/" + str.C_Str();
		texture.id = App->textures->Load(fullPath.c_str());
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}

	return textures;
}

void ComponentMesh::Draw( ) 
{
	Shader shader = my_go->shader;
	shader.Use();
	aiMatrix4x4 t = my_go->transform->worldTransform;
	t.Transpose();

	glm::mat4 projection = App->camera_editor->mainCamera.getProjectionMatrix();
	glm::mat4 view = App->camera_editor->mainCamera.getViewMatrix();

	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, (float*)&t);
	
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}

}

update_status ComponentMesh::Update() 
{
	Draw();
	return UPDATE_CONTINUE;
}