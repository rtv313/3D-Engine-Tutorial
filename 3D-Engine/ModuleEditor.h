#ifndef _MODULE_EDITOR_H
#define _MODULE_RENDER_H

#include "Module.h"
#include "Globals.h"

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
};
#endif