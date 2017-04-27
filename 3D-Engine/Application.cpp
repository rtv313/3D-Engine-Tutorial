#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCameraEditor.h";
#include  "ModuleEditor.h"
using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera_editor = new ModuleCameraEditor());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(audio = new ModuleAudio());
	
	// Modules to draw on top of game logic
	modules.push_back(fade = new ModuleFadeToBlack());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}



	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	miliseconds.start();

	if (resetTimer == true) 
	{
		timerFPS.start();
		start = timerFPS.read();
		resetTimer = false;
	}

	calculateDeltaTime();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	++fpsCounter;

	float timeForFrame = miliseconds.read();
	App->editor->confWindow.addMiliseconds(timeForFrame);

	if (timerFPS.read() >= SECOND + start) // One second pased
	{
		App->editor->log.AddLog("FPS:%d \n",fpsCounter + 10);
		App->editor->confWindow.addFps(fpsCounter + FRAME_ADJUSTMENT);
		fpsCounter = 0;
		resetTimer = true;
	}

	Uint32 delayTime = abs(SECOND / FPS_CAP);
	SDL_Delay(delayTime);

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

void Application::calculateDeltaTime() 
{
	GLfloat currentFrame = SDL_GetTicks();
	deltaTime =( currentFrame - lastFrame)/1000;
	lastFrame = currentFrame;
}

