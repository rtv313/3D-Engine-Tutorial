#ifndef __MODULE_CAMERA_EDITOR_H
#define __MODULE_CAMERA_EDITOR_H
#include "Globals.h"
#include "Module.h"


class ModuleCameraEditor :public Module 
{
public:
	ModuleCameraEditor();
	~ModuleCameraEditor();
	
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

};


#endif // !__MODULE_CAMERA_EDITOR_H
