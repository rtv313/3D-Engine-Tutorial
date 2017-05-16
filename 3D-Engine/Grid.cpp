#include "Grid.h"
#include "Application.h"
#include "ModuleCameraEditor.h";
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define SIZE 50
Grid::Grid()
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	
	uint id = 0;
	int indexID = 0;

	for (int i = -SIZE / 2; i <= SIZE / 2; i++)
	{
		indices.push_back(id); id++;
		verticesHorizontal.push_back(SIZE / 2);
		verticesHorizontal.push_back(0); 
		verticesHorizontal.push_back(i);

		indices.push_back(id); id++;
		verticesHorizontal.push_back( -SIZE / 2);
		verticesHorizontal.push_back(0); 
		verticesHorizontal.push_back(i); 
	}
	
	for (int i = -SIZE / 2; i <= SIZE / 2; i++)
	{
		verticesVertical.push_back(i); 
		verticesVertical.push_back(0); 
		verticesVertical.push_back(-SIZE / 2);

		verticesVertical.push_back(i); 
		verticesVertical.push_back(0); 
		verticesVertical.push_back(SIZE / 2);
	}



	this->indicesSize = sizeof(GLuint) *indices.size();
	
	//Horizontal lines
	glGenVertexArrays(1, &this->VAOh);
	glGenBuffers(1, &this->VBOh);
	glGenBuffers(1, &this->EBOh);

	glBindVertexArray(VAOh);

	glBindBuffer(GL_ARRAY_BUFFER, VBOh);
	glBufferData(GL_ARRAY_BUFFER, verticesHorizontal.size() * sizeof(GLfloat), &verticesHorizontal[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOh);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) *indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	//Vertical lines
	glGenVertexArrays(1, &this->VAOv);
	glGenBuffers(1, &this->VBOv);
	glGenBuffers(1, &this->EBOv);

	glBindVertexArray(VAOv);

	glBindBuffer(GL_ARRAY_BUFFER, VBOv);
	glBufferData(GL_ARRAY_BUFFER, verticesVertical.size() * sizeof(GLfloat), &verticesVertical[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOv);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader = new Shader(pVSFileName, pFSFileName);
}

Grid::~Grid()
{
	delete shader;
	glDeleteVertexArrays(1, &VAOh);
	glDeleteBuffers(1, &VBOh);
	glDeleteBuffers(1, &EBOh);

	glDeleteVertexArrays(1, &VAOv);
	glDeleteBuffers(1, &VBOv);
	glDeleteBuffers(1, &EBOv);
}

void Grid::Draw()
{
	shader->Use();

	// camera
	glm::mat4 view = App->camera_editor->mainCamera.getViewMatrix();
	glm::mat4 projection = App->camera_editor->mainCamera.getProjectionMatrix();

	//Colors
	GLint objectColorLoc = glGetUniformLocation(shader->Program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader->Program, "lightColor");
	glUniform3f(objectColorLoc, red, green, blue);
	glUniform3f(lightColorLoc, 0.5f, 0.5f,0.5f);

	//Uniform Location
	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");

	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw container
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX,posY, posZ));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAOh);
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAOv);
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}