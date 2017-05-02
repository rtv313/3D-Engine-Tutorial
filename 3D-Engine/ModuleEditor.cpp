#include "Globals.h"
#include "Application.h"
#include "Glew/include/GL/glew.h" // extension lib
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"




ModuleEditor::ModuleEditor() 
{
	
}

ModuleEditor::~ModuleEditor()
{


}

bool ModuleEditor::Init() 
{
	
	ImGui_ImplSdlGL3_Init(App->window->window);
	return true;
}

bool ModuleEditor::Start() 
{
	return true;
}

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	ImGui::ShowTestWindow();
	//ImGui::Begin("Sample window"); 
	//

	//ImGui::InputText("Window title", text, 255);
	//ImGui::SliderFloat("float",&f,0.0f,1.0f);
	//

	//ImGui::End(); // end window
	confWindow.Draw();
	menu.Draw();
	hierarchyWindow.Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	
	log.Draw("Console");
	ImGui::Render();
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() 
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}