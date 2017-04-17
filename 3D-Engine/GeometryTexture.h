#ifndef  __TUTORIAL_TEXTURE_H_
#define  __TUTORIAL_TEXTURE_H_
#include "Glew/include/GL/glew.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Shader.h"

class TutorialTexture 
{
public:
	const char* pVSFileName = "../shaderTexture.vs";
	const char* pFSFileName = "../shaderTexture.fs";
	
	TutorialTexture() 
	{
		 shader= Shader(pVSFileName, pFSFileName);

		 GLuint indices[] = {  // Note that we start from 0!
			 0, 1, 3, // First Triangle
			 1, 2, 3  // Second Triangle
		 };

		 GLfloat vertices[] = {
			 // Positions          // Colors           // Texture Coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
			 -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
		 };

		 glGenVertexArrays(1, &VAO);
		 glGenBuffers(1, &VBO);
		 glGenBuffers(1, &EBO);

		 glBindVertexArray(VAO);

		 glBindBuffer(GL_ARRAY_BUFFER, VBO);
		 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		 // Position attribute
		 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		 glEnableVertexAttribArray(0);
		 // Color attribute
		 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		 glEnableVertexAttribArray(1);
		 // TexCoord attribute
		 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		 glEnableVertexAttribArray(2);

		 glBindVertexArray(0); // Unbind VAO

		 // ====================
		 // Texture 1
		 // ====================

		 texture1= App->textures->Load("../Textures/container.jpg");
		 texture2 = App->textures->Load("../Textures/awesomeface.png");

	}
	~TutorialTexture() 
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void draw() 
	{
		// Activate shader
		shader.Use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

private:
	GLuint VBO, VAO, EBO;
	GLuint texture1;
	GLuint texture2;
	Shader shader;
};


#endif

