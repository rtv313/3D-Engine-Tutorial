#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
#include <string>
#include <vector>
#include "Globals.h"
#include "ComponentTransform.h"
#include "Shader.h"
class GameObject
{
public:
	GameObject(aiNode* node, const aiScene* scene, std::string directory);
	~GameObject();
	void Update();
	void addChild(GameObject * child);
	void RemoveNode(GameObject * childToRemove);
	bool active;
	std::string name;
	std::vector<Component*> components;
	std::vector<GameObject*> childs;
	Shader shader;
	GameObject * parent;
	ComponentTransform * transform;
	std::string directory;	
};

#endif // !GAME_OBJECT_H_

