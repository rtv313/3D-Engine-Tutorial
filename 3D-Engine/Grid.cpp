#include "Grid.h"
#include "Application.h"
#include "ModuleCameraEditor.h";
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Grid::Grid()
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;

	size = 8; 

	//x,y,z * 2 for the two points needed for a line and *2 for the vertical lines
	vertices = new GLfloat[size*3*2]; 
	indices = new GLuint[size*2];
	int componentVertexIndex = 0;
	int id = 0;

	GLfloat x = -(GLfloat)(size/2);
	int counterVertices = 0;
	int indexID = 0;

	for (int i = 0; i < size; i++) 
	{
		//horizontal lines
		vertices[counterVertices] = x; counterVertices++; // first point
		vertices[counterVertices] = 0.0; counterVertices++;
		vertices[counterVertices] = size; counterVertices++;
		indices[indexID] = indexID;
		indexID++;

		vertices[counterVertices] = x; counterVertices++; // second point
		vertices[counterVertices] = 0.0; counterVertices++;
		vertices[counterVertices] = -size; counterVertices++;
		indices[indexID] = indexID;
		indexID++;

		// vertical lines

		//vertices[counterVertices] = size; counterVertices++; // first point
		//vertices[counterVertices] = 0.0; counterVertices++;
		//vertices[counterVertices] = x; counterVertices++;
		//indices[indexID] = indexID;
		//indexID++;

		//vertices[counterVertices] = -size; counterVertices++; // second point
		//vertices[counterVertices] = 0.0; counterVertices++;
		//vertices[counterVertices] = x; counterVertices++;
		//indices[indexID] = indexID;
		//indexID++;
		//
		x++;
	}



	indicesSize = indexID;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size*24, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) *indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
	shader = new Shader(pVSFileName, pFSFileName);
	
}

Grid::~Grid()
{
	delete vertices;
	delete indices;
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}