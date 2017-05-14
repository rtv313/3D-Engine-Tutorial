#include "Grid.h"
#include "Application.h"
#include "ModuleCameraEditor.h";
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#define VERTEX_FOR_LINE 6
#define INDECES_FOR_LINE 2
Grid::Grid()
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	
	int size = 15;
	//x,y,z * 2 for the two points needed for a line and *2 for the vertical lines
	verticesHorizontal = new GLfloat[size *VERTEX_FOR_LINE];
	indices = new GLuint[size *INDECES_FOR_LINE];
	verticesVertical = new GLfloat[size * VERTEX_FOR_LINE];

	int componentVertexIndex = 0;
	int id = 0;

	GLfloat x = -(GLfloat)(size /2);
	int indexID = 0;

	for (int i = -size / 2; i <= size / 2; i++)
	{
		indices[id] = id; id++;
		verticesHorizontal[componentVertexIndex] = size / 2; componentVertexIndex++;
		verticesHorizontal[componentVertexIndex] = 0; componentVertexIndex++;
		verticesHorizontal[componentVertexIndex] = i; componentVertexIndex++;

		indices[id] = id; id++;
		verticesHorizontal[componentVertexIndex] = -size / 2; componentVertexIndex++;
		verticesHorizontal[componentVertexIndex] = 0; componentVertexIndex++;
		verticesHorizontal[componentVertexIndex] = i; componentVertexIndex++;
	}

	componentVertexIndex = 0;

	for (int i = -size / 2; i <= size / 2; i++)
	{
		verticesVertical[componentVertexIndex] = i; componentVertexIndex++;
		verticesVertical[componentVertexIndex] = 0; componentVertexIndex++;
		verticesVertical[componentVertexIndex] = -size / 2; componentVertexIndex++;

		verticesVertical[componentVertexIndex] = i; componentVertexIndex++;
		verticesVertical[componentVertexIndex] = 0; componentVertexIndex++;
		verticesVertical[componentVertexIndex] = size / 2; componentVertexIndex++;
	}



	indicesSize = id;


	//Horizontal lines
	glGenVertexArrays(1, &this->VAOh);
	glGenBuffers(1, &this->VBOh);
	glGenBuffers(1, &this->EBOh);

	glBindVertexArray(VAOh);

	glBindBuffer(GL_ARRAY_BUFFER, VBOh);
	glBufferData(GL_ARRAY_BUFFER, size *24, verticesHorizontal, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOh);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) *indicesSize, indices, GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, size * 24, verticesVertical, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOv);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader = new Shader(pVSFileName, pFSFileName);
	
}

Grid::~Grid()
{
	delete verticesHorizontal;
	delete indices;
	delete verticesVertical;
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