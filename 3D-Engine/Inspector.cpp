#include "Inspector.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "glm/gtc/matrix_transform.hpp"

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

	if (gameObject != nullptr)
	{
		ImVec4 color(255, 0, 0, 1);
		ImGui::TextColored(color, gameObject->name.c_str());
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Transform"))
		{
			aiVector3D position = gameObject->transform->position;
			static float positionArray[3] = { position.x, position.y, position.z };
			ImGui::DragFloat3("Position", positionArray);
			position.x = positionArray[0];
			position.y = positionArray[1];
			position.z = positionArray[2];
			gameObject->transform->position = position;
			ImGui::Separator();

			aiVector3D scale = gameObject->transform->scale;
			static float scaleArray[3] = { scale.x, scale.y, scale.z };
			ImGui::DragFloat3("Scale", scaleArray);
			scale.x = scaleArray[0];
			scale.y = scaleArray[1];
			scale.z = scaleArray[2];
			gameObject->transform->scale = scale;
			ImGui::Separator();


			aiVector3D rotation;
			static float rotationArray[4] = { rotation.x, rotation.y, rotation.z,0.1f };
			ImGui::DragFloat3("Rotation", rotationArray);

			rotation.x = rotationArray[0];
			rotation.y = rotationArray[1];
			rotation.z = rotationArray[2];

			aiQuaternion rotX = aiQuaternion(aiVector3D(1.0, 0.0, 0.0), glm::radians(rotation.x));
			aiQuaternion rotY = aiQuaternion(aiVector3D(0.0, 1.0, 0.0), glm::radians(rotation.y));
			aiQuaternion rotZ = aiQuaternion(aiVector3D(0.0, 0.0, 1.0), glm::radians(rotation.z));


			aiQuaternion finalRotation;
			finalRotation = finalRotation*rotX;
			finalRotation = finalRotation*rotY;
			finalRotation = finalRotation*rotZ;
			
			gameObject->transform->rotation = finalRotation;
		}

	}

	ImGui::End();
}

