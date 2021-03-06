#include "FpsGraph.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

FpsGraph::FpsGraph() 
{
	fps_log.push_back(0.0);
	ms_log.push_back(0.0);
}

void FpsGraph::addFps(float fps) 
{
	if (fps_log.size() >= 180) 
	{
		fps_log.erase(fps_log.begin());
	}
		
	fps_log.push_back(fps);
}

void FpsGraph::addMiliseconds(float milisecond) 
{
	if (ms_log.size() >= 50)
	{
		ms_log.erase(ms_log.begin());
	}

	ms_log.push_back(milisecond *10);
}

void FpsGraph::Draw()
{
	ImGui::Begin("Frame Rate");

	sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
	ImGui::Text(title);
	ImGui::Spacing();
	ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, "", 0.0f, 100.0f, ImVec2(310, 100));
	ImGui::Spacing();
	
	sprintf_s(title, 25, "Miliseconds rate %.1f", ms_log[ms_log.size() - 1]);
	ImGui::Text(title);
	ImGui::Spacing();
	ImGui::PlotHistogram("milisecondsrate", &ms_log[0], ms_log.size(), 0, "", 0.0f, 100.0f, ImVec2(310, 100));

	ImGui::End(); // end window
}