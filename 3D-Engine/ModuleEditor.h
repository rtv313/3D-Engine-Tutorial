#ifndef _MODULE_EDITOR_H
#define _MODULE_RENDER_H

#include "Module.h"
#include "Globals.h"
#include "ConsoleLog.h"
#include "Menu.h"
#include "FpsGraph.h"
#include "ConfigurationWindow.h"
#include "HierarchyWindow.h"
#include "Inspector.h"

class ModuleEditor : public Module 
{
public:
	ModuleEditor();
	~ModuleEditor();
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	Log log;
	Menu menu;
	ConfigurationWindow confWindow;
	HierarchyWindow  hierarchyWindow;
	Inspector inspector;
};
#endif