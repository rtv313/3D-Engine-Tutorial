#ifndef _GRAPH_NODE_H
#define _GRAPH_NODE_H
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "GraphMesh.h"
#include "SceneGraph.h"

class GraphNode 
{
public:
	std::string name;
	aiVector3D position = aiVector3D(0, 0, 0);
	aiVector3D scale = aiVector3D(1, 1, 1);
	aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
	std::vector<GraphMesh> meshes; //reference to meshes in scene graph vector
	GraphNode * parent = nullptr;
	std::vector<GraphNode*> childs;
	std::string directory;


	GraphNode(aiNode* node, const aiScene* scene,std::string directory)
	{
		// Process each mesh located at the current node
		this->directory = directory;
		this->name = node->mName.C_Str();
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh,scene));
		}
	}


	~GraphNode() 
	{
		for (int i = 0; i < childs.size(); i++)
		{
			for (int u = 0; u < childs[i]->meshes.size(); u++)
				childs[i]->meshes[u].DeleteMeshBuffers();
		}

		childs.clear();
	}

	void addChild(GraphNode * child)
	{
		childs.push_back(child);
	}


	GraphMesh processMesh(aiMesh * mesh, const aiScene* scene) 
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
			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			std::vector<TextureGraph> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. Specular maps
			std::vector<TextureGraph> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		// Return a mesh object created from the extracted mesh data
		return GraphMesh(vertices, indices, textures, mesh->mMaterialIndex);
	}


	std::vector<TextureGraph> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<TextureGraph> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			TextureGraph texture;
			std::string fullPath = this->directory + "/" + str.C_Str();
			texture.id = App->textures->Load(fullPath.c_str());
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
		}

		return textures;
	}

	 
	void Draw(Shader shader, aiMatrix4x4 parentModel)
	{
		
		//  Draw(Shader shader,glm::mat4 parentModel)
		glm::mat4 model;
		aiMatrix4x4 m(scale, rotation, position);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z)) * glm::rotate(model, rotation.y, glm::vec3(0.0, 1.0, 0.0))* glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
		aiMatrix4x4 worldTransform = parentModel * m;

		aiMatrix4x4 t  = worldTransform;
		t.Transpose();

		//glm::mat4 mat = aiMatrix4x4ToGlm(&worldTransform);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, (float*)&t); 
		for (int i = 0; i < meshes.size(); i++) 
		{
			meshes[i].Draw(shader);
		}

		for (int i = 0; i < childs.size(); i++) 
		{
			childs[i]->Draw(shader, worldTransform); // antes model
		}
	}

	glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from)
	{
		glm::mat4 to;


		to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
		to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
		to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
		to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;

		return to;
	}

	void RemoveNode(GraphNode* nodeToRemove) 
	{
		for (int i = 0; i < childs.size(); i++) 
		{
			if (childs[i] == nodeToRemove) 
			{
				childs.erase(childs.begin() + i);
				return;
			}
		}
		return;
	}

};
#endif // !_GRAPH_NODE_H

