#include "Inspector.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "glm/gtc/matrix_transform.hpp"

static float positionArray[3] = {0.0,0.0,.0};
static float scaleArray[3] = { 1.0, 1.0, 1.0};
static float rotationArray[3] = { 0.0,0.0,0.0};

Inspector::Inspector() 
{
}

Inspector::~Inspector() 
{
}

void Inspector::Draw() 
{
	ImGui::Begin("Inspector");
	ImGui::Text("Inspector");


	if (gameObjectActual != nullptr)
	{
		ImVec4 color(255, 0, 0, 1);
		ImGui::TextColored(color, gameObjectActual->name.c_str());
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Transform"))
		{
			aiVector3D position = gameObjectActual->transform->position;
			positionArray[0] = position.x;
			positionArray[1] = position.y;
			positionArray[2] = position.z;
			ImGui::DragFloat3("Position", positionArray);
			position.x = positionArray[0];
			position.y = positionArray[1];
			position.z = positionArray[2];
			gameObjectActual->transform->position = position;
			ImGui::Separator();
			////////////////////////////////////////////////////////////////////
			aiVector3D scale = gameObjectActual->transform->scale;
			scaleArray[0] = scale.x;
			scaleArray[1] = scale.y;
			scaleArray[2] = scale.z;
			ImGui::DragFloat3("Scale", scaleArray);
			scale.x = scaleArray[0];
			scale.y = scaleArray[1];
			scale.z = scaleArray[2];
			gameObjectActual->transform->scale = scale;
			ImGui::Separator();
			////////////////////////////////////////////////////////////////////////

			aiVector3D rotation = gameObjectActual->transform->rotationDegrees;
			rotationArray[0] = rotation.x; 
			rotationArray[1] = rotation.y;
			rotationArray[2] = rotation.z;

			ImGui::DragFloat3("Rotation", rotationArray);

			gameObjectActual->transform->rotationDegrees.x = rotationArray[0];
			gameObjectActual->transform->rotationDegrees.y = rotationArray[1];
			gameObjectActual->transform->rotationDegrees.z = rotationArray[2];
			
		}

	}

	ImGui::End();
}


void Inspector::ChangeObject(GameObject * const newGameObject) 
{
	gameObjectActual = newGameObject;
}
