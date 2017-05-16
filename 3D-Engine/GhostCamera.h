#ifndef GHOST_CAMERA_H
#define GHOST_CAMERA_H
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Shader.h"
#include <vector>

#define INDICES_CUBE 32

class GhostCamera
{
public:
	float3 position;
	GhostCamera();
	~GhostCamera();
	void Draw();
private:
	Frustum frustum;
	float3 corners[8];
	GLuint VBO, VAO, EBO;
	GLuint indices[INDICES_CUBE]=
	{
		1,5,7,3,
		4,0,2,6,
		5,4,6,7,
		5,7,6,4,
		0,1,3,2,
		0,2,1,3,
		3,7,6,2,
		0,4,5,1
	};
	std::vector <float3> verticesVec;
	GLuint  indicesSize=0;
	Shader* shader;
	GLfloat red = 250, blue = 0, green = 158;
	const char* pVSFileName = "../lighting.vs";
	const char* pFSFileName = "../lighting.fs";
};

#endif // !GHOST_CAMERA_H

