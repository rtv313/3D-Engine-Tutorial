#ifndef  __TUTORIAL_3_H
#define  __TUTORIAL_3_H

#include "Glew/include/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/vec3.hpp" 
class BasicTriangle
{	
public:
	glm::vec3 Vertices[3];
	GLuint VBO=0;

	BasicTriangle() {
		Vertices[0] = glm::vec3(-1.0f, -0.5f, -4.0f);
		Vertices[1] = glm::vec3(1.0f, -0.5f, -4.0f);
		Vertices[2] = glm::vec3(0.0f, 0.5f, -4.0f);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	}

	~BasicTriangle() 
	{
		glDeleteBuffers(1,&VBO);
	}

	void draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
};


#endif 