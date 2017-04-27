#ifndef _MODULE_EDITOR_H
#define _MODULE_RENDER_H

#include "Module.h"
#include "Globals.h"
#include "ConsoleLog.h"
#include "Menu.h"
#include "FpsGraph.h"
#include "ConfigurationWindow.h"

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
	char * text ="hola";
	float f=0.0;
	Log log;
	Menu menu;
	ConfigurationWindow confWindow;
	
};
#endif