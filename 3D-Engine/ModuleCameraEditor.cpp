#include "ModuleCameraEditor.h";
#include "Glew/include/GL/glew.h"
#include <gl/GL.h>

ModuleCameraEditor::ModuleCameraEditor()
{
}


ModuleCameraEditor::~ModuleCameraEditor()
{
}

update_status ModuleCameraEditor::PreUpdate() 
{
	mainCamera.do_movement();
	mainCamera.mouse_movement();
	return UPDATE_CONTINUE;
}
update_status ModuleCameraEditor::Update() 
{
	
	return UPDATE_CONTINUE;
}
update_status ModuleCameraEditor::PostUpdate() 
{
	return UPDATE_CONTINUE;
}