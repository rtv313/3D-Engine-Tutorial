#ifndef GRID_H
#define GRID_H
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "Shader.h"
#include <vector>
class Grid 
{
public:
	GLfloat posX, posY, posZ;
	GLfloat red = 255, blue = 255, green = 255;
	
	const char* pVSFileName = "../lighting.vs";
	const char* pFSFileName = "../lighting.fs";
	Grid();
	~Grid();
	void Draw();
private:
	GLuint VBO, VAO, EBO;
	int size;
	GLfloat *vertices;
	GLuint * indices;
	uint indicesSize = 0;
	Shader *shader;
	
};
	
#endif // !GRID_H

