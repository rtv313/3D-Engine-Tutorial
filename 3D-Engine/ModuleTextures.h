#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__
#include<map>
#include "Globals.h"
#include "Module.h"
#include "Glew/include/GL/glew.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();
	bool Init();
	bool CleanUp();
	GLuint const Load(const char* path);
	std::map <std::string, GLuint> textures;
private:
	
};

#endif // __MODULETEXTURES_H__