#include "Menu.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include <shlobj.h>


Menu::Menu()
{

}

void Menu::Draw()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("Menu")) 
	{
		if(ImGui::MenuItem("Menu Item"))
			ShellExecute(0, 0,"http://www.google.com", 0, 0, SW_SHOW);
		ImGui::EndMenu();
	}
	
	ImGui::EndMainMenuBar();
}