#ifndef  HIERARCHY_WINDOW_H
#define HIERARCHY_WINDOW_H
#include <vector>

class GameObject;



class HierarchyWindow 
{
public:
	GameObject* selectedGameObject=nullptr;
	HierarchyWindow();
	~HierarchyWindow();
	void DrawTree(GameObject* node);
	void Draw();
};

#endif