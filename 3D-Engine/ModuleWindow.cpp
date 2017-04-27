#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment( lib, "opengl32.lib")
#pragma comment( lib, "glu32.lib")
#pragma comment( lib, "Glew/lib/Release/Win32/glew32.lib" )

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		width = SCREEN_WIDTH * SCREEN_SIZE;
		height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		flags |= SDL_WINDOW_OPENGL;
		flags |= SDL_WINDOW_RESIZABLE;
		
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		SDL_GL_CreateContext(window);

		//Opengl initialization
		GLenum err = glewInit();

		if (err != GLEW_OK)
		{
			fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
			return 1;
		}

		LOG("Using Glew %s", glewGetString(GLEW_VERSION));
		// Should be 2.0
		LOG("Vendor: %s", glGetString(GL_VENDOR));
		LOG("Renderer: %s", glGetString(GL_RENDERER));
		LOG("OpenGL version supported %s", glGetString(GL_VERSION));
		LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		if(window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window and opengl context
	if (window != nullptr)
	{
		SDL_GL_DeleteContext(window);
		SDL_DestroyWindow(window);
	}
	
	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::changeResolution(int width, int height)
{
	
	SDL_SetWindowSize(window, width*SCREEN_SIZE, height*SCREEN_SIZE);
}

void ModuleWindow::SetFullScreen(bool fullscreen,bool fullscreenDesk) 
{
	Uint32 flags;

	if (fullscreen == true)
		flags |= SDL_WINDOW_FULLSCREEN;

	if (fullscreenDesk == true)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_SetWindowFullscreen(window, flags);

}