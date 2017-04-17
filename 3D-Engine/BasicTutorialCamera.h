#ifndef  __TUTORIAL_BASIC_CAMERA_H_
#define  __TUTORIAL_BASIC_CAMERA_H_

#include "Glew/include/GL/glew.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SDL/include/SDL.h"
#include "Camera.h"

class TutorialBasicCamera
{
public:
	const char* pVSFileName = "../shaderTutorialTransformProjectionViewModel.vs";
	const char* pFSFileName = "../shaderTexture.fs";
	Camera cam;

	TutorialBasicCamera()
	{
		shader = Shader(pVSFileName, pFSFileName);


		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};



		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0); // Unbind VAO

							  // ====================
							  // Texture 1
							  // ====================

		texture1 = App->textures->Load("../Textures/container.jpg");
		texture2 = App->textures->Load("../Textures/awesomeface.png");

	}
	~TutorialBasicCamera()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

	}

	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
		glEnable(GL_DEPTH_TEST); // z-finding

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		cam.do_movement();
		cam.mouse_movement();
		cam.scroll_movement();
		//scroll_movement(App->input->GetMouseWheelMotion().x);
		

		// Activate shader
		shader.Use();
		// Camera/View transformation
		glm::mat4 view = cam.getViewMatrix();
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Projection 
		glm::mat4 projection = cam.getProjectionMatrix();
		//projection = glm::perspective(fov, (GLfloat)App->window->width / (GLfloat)App->window->height, 0.1f, 100.0f);

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");

		// Get matrix's uniform location and set matrix
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);

		// World space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		// Draw container
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		glDisable(GL_DEPTH_TEST);
	}

private:
	GLuint VBO, VAO;
	GLuint texture1;
	GLuint texture2;
	Shader shader;

	// Camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	GLfloat pitch = 0.0f;
	GLfloat lastX = App->window->width / 2.0;
	GLfloat lastY = App->window->height / 2.0;
	GLfloat fov = 45.0f;

	iPoint mousePosition={0,0};

	bool firstMouse = true;

	void do_movement() 
	{
		// Camera controls
		GLfloat cameraSpeed = 5.0f * App->deltaTime;

		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
			cameraPos.y += cameraSpeed;
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
			cameraPos.y -= cameraSpeed;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			cameraPos += cameraSpeed * cameraFront;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			cameraPos -= cameraSpeed * cameraFront;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	//void mouse_movement()
	//{
	//	if (App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT) 
	//	{
	//		return;
	//	}

	//	iPoint mouseNewPosition = App->input->GetMousePosition();

	//	if (firstMouse)
	//	{
	//		mousePosition.x = mouseNewPosition.x;
	//		mousePosition.y = mouseNewPosition.y;
	//		firstMouse = false;
	//	}

	//	GLfloat xoffset = (mouseNewPosition.x - mousePosition.x);
	//	GLfloat yoffset = (mousePosition.y - mouseNewPosition.y); // Reversed since y-coordinates go from bottom to left
	//
	//	GLfloat sensitivity = 0.1;	// Change this value to your liking
	//	xoffset *= sensitivity;
	//	yoffset *= sensitivity;

	//	yaw += xoffset;
	//	pitch += yoffset;


	//	mousePosition = mouseNewPosition;

	//	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//	if (pitch > 89.0f)
	//		pitch = 89.0f;
	//	if (pitch < -89.0f)
	//		pitch = -89.0f;

	//

	//	glm::vec3 front;
	//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	front.y = sin(glm::radians(pitch));
	//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	cameraFront = glm::normalize(front);

	//
	//}

	void mouse_movement()
	{
		if (App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT)
		{
			return;
		}

		iPoint mouseNewPosition = App->input->GetMousePosition();

		if (mouseNewPosition.x > mousePosition.x) 
		{
			yaw++;
		}

		if (mouseNewPosition.x < mousePosition.x)
		{
			yaw--;
		}
		
		if (mouseNewPosition.y > mousePosition.y)
		{
			pitch--;
		}

		if (mouseNewPosition.y < mousePosition.y)
		{
			pitch++;
		}


		mousePosition = mouseNewPosition;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;



		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}


	void scroll_movement(double yoffset)
	{
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= yoffset*App->deltaTime;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;
	}

};

#endif