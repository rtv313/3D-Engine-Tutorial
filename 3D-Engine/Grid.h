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
	Grid();
	~Grid();
	void Draw();
private:
	GLuint VBOh, VAOh, EBOh;
	GLuint VBOv, VAOv, EBOv;
	int size;
	std::vector<GLfloat> verticesHorizontal;
	std::vector<GLfloat> verticesVertical;
	std::vector<GLuint> indices;
	GLuint indicesSize = 0;
	Shader *shader;
	const char* pVSFileName = "../lighting.vs";
	const char* pFSFileName = "../lighting.fs";
};
	
#endif // !GRID_H

