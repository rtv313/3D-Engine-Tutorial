#include <stdio.h>
#include "HierarchyWindow.h"
#include "Application.h"
#include "ModuleScene.h"
HierarchyWindow::HierarchyWindow() 
{

}

HierarchyWindow::~HierarchyWindow()
{

}

void HierarchyWindow::Draw() 
{
	ImGui::Begin("Hierarchy");
	if (ImGui::TreeNode("Scene"))
	{
		DrawTree(App->scene->root);
		ImGui::TreePop();
	}
	ImGui::End();
}

void HierarchyWindow::DrawTree(GameObject* node)
{
	if(ImGui::TreeNode(node->name.c_str()))
	{
		for (int i = 0; i < node->childs.size(); i++)
		{
			if (ImGui::TreeNode(node->childs[i]->name.c_str()))
			{
				DrawTree(node->childs[i]);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}
