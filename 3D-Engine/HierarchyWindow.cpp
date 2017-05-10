#include <stdio.h>
#include "HierarchyWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "ModuleEditor.h"

HierarchyWindow::HierarchyWindow() 
{

}

HierarchyWindow::~HierarchyWindow()
{

}

void HierarchyWindow::Draw() 
{
	ImGui::Begin("Hierarchy");
	ImGui::Text("Hierarchy");

	if (ImGui::TreeNode("Scene"))
	{
		DrawTree(App->scene->root);
		ImGui::TreePop();
	}
	ImGui::End();
}

void HierarchyWindow::DrawTree(GameObject* node)
{
	int static fatherNode = 0;
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
	App->editor->inspector.gameObject = selectedGameObject;
	
	if (selectedGameObject == node)
		node_flags |= ImGuiTreeNodeFlags_Selected;

	if (node->childs.size() > 0) // node
	{
		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)fatherNode, node_flags, node->name.c_str());
		
		
		if (ImGui::IsItemClicked())
			selectedGameObject = node;

		if (node->childs.size() > 0 && node_open)
		{
			for (int i = 0; i < node->childs.size(); i++)
			{
				DrawTree(node->childs[i]);

			}
			ImGui::TreePop();
		}
	}
	else  // leaf
	{
		ImGui::TreeNodeEx((void*)(intptr_t)fatherNode, node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, node->name.c_str());
		
		if (ImGui::IsItemClicked())
			selectedGameObject = node;
	}
}

