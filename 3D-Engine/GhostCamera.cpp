#include "GhostCamera.h"
#include "Application.h"
#include "ModuleCameraEditor.h";
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define CUBE_POINTS 8

GhostCamera::GhostCamera()
{
	
	position = float3(0.0,0.0,0.0);
	frustum.SetPos(position);
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetPerspective(45,45); 
	frustum.SetViewPlaneDistances(1.0f,5.0f);
	frustum.GetCornerPoints(corners);

	indicesSize = sizeof(GLuint) * INDICES_CUBE;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, CUBE_POINTS * sizeof(float3), corners, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader = new Shader(pVSFileName, pFSFileName);
}

GhostCamera::~GhostCamera()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete shader;
}

void GhostCamera::Draw() 
{
	shader->Use();

	// camera
	glm::mat4 view = App->camera_editor->mainCamera.getViewMatrix();
	glm::mat4 projection = App->camera_editor->mainCamera.getProjectionMatrix();

	//Colors
	GLint objectColorLoc = glGetUniformLocation(shader->Program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader->Program, "lightColor");
	glUniform3f(objectColorLoc, red, green, blue);
	glUniform3f(lightColorLoc, 0.5f, 0.5f, 0.5f);

	//Uniform Location
	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");

	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw container
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}