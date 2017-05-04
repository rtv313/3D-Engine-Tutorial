#include <stdio.h>
#include "HierarchyWindow.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "assimp/include/assimp/quaternion.h"
HierarchyWindow::HierarchyWindow() 
{

}

HierarchyWindow::~HierarchyWindow()
{

}

void HierarchyWindow::Draw() 
{
	ImGui::Begin("Hierarchy");
	ImGui::Columns(2, "Hierarchy");
	ImGui::Separator();
	ImGui::Text("Hierarchy");

	if (ImGui::TreeNode("Scene"))
	{
		DrawTree(App->scene->root);
		ImGui::TreePop();
	}

	ImGui::NextColumn();
	ImGui::Text("Game Object");

	if (selectedGameObject != nullptr) 
	{
		ImVec4 color(255,0,0,1);
		ImGui::TextColored(color,selectedGameObject->name.c_str());
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Transform")) 
		{
			aiVector3D position = selectedGameObject->transform->position;
			static float positionArray[3] = { position.x, position.y, position.z };
			ImGui::DragFloat3("Position", positionArray);
			position.x = positionArray[0];
			position.y = positionArray[1];
			position.z = positionArray[2];
			selectedGameObject->transform->position = position;
			ImGui::Separator();

			aiVector3D scale  = selectedGameObject->transform->scale;
			static float scaleArray[3] = { scale.x, scale.y, scale.z };
			ImGui::DragFloat3("Scale", scaleArray);
			scale.x = scaleArray[0];
			scale.y = scaleArray[1];
			scale.z = scaleArray[2];
			selectedGameObject->transform->scale = scale;
			ImGui::Separator();


			aiVector3D rotation; 
			static float rotationArray[4] = { rotation.x, rotation.y, rotation.z,0.1f };
			ImGui::DragFloat3("Rotation", rotationArray);

			rotation.x = rotationArray[0];
			rotation.y = rotationArray[1];
			rotation.z = rotationArray[2];

			aiQuaternion rotX = aiQuaternion(aiVector3D(1.0,0.0,0.0), rotation.x*0.1);
			aiQuaternion rotY = aiQuaternion(aiVector3D(0.0, 1.0, 0.0),rotation.y*0.1);
			aiQuaternion rotZ = aiQuaternion(aiVector3D(0.0, 0.0, 1.0), rotation.z*0.1);
			

			aiQuaternion finalRotation;
			finalRotation = finalRotation*rotX;
			finalRotation = finalRotation*rotY;
			finalRotation = finalRotation*rotZ;
			

			
			selectedGameObject->transform->rotation = finalRotation;
		}
			
	}

	ImGui::Separator();
	ImGui::End();
}

void HierarchyWindow::DrawTree(GameObject* node)
{
	if(ImGui::TreeNode(node->name.c_str()))
	{
		selectedGameObject = node;
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
