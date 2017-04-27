#ifndef  CONSOLE_LOG_H
#define CONSOLE_LOG_H
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

class Log
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset
	bool                ScrollToBottom;

public:
	Log();
	void Clear();
	void AddLog(const char* fmt, ...) IM_PRINTFARGS(2);
	void Draw(const char* title, bool* p_opened = NULL);
};
#endif
