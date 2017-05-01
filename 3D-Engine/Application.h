#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#define SECOND 1000.0
#define FRAME_ADJUSTMENT 10  // WE USE IT FOR DELAY BECAUSE VSYNC BUG ONLY WORKS IN FULLSCREEN

#include<list>
#include "Globals.h"
#include "Module.h"
#include "TempMili.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCameraEditor;
class ModuleEditor;
class ModuleScene;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCameraEditor * camera_editor;
	ModuleEditor * editor;
	ModuleScene * scene;
	float deltaTime;
	float lastFrame;

private:
	TempMili timerFPS;
	TempMili miliseconds;
	double start;
	int fpsCounter=0;
	bool resetTimer = true;
	std::list<Module*> modules;
	void calculateDeltaTime();
	
};

extern Application* App;

#endif // __APPLICATION_CPP__