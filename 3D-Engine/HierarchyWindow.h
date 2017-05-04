#ifndef  HIERARCHY_WINDOW_H
#define HIERARCHY_WINDOW_H
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

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