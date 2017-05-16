#ifndef  __CAMERA_H_
#define  __CAMERA_H_

#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "Glew/include/GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"



// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
//enum Camera_Movement {
//	FORWARD,
//	BACKWARD,
//	LEFT,
//	RIGHT
//};
//
//// Default camera values
//const GLfloat YAW = -90.0f;
//const GLfloat PITCH = 0.0f;
//const GLfloat SPEED = 3.0f;
//const GLfloat SENSITIVTY = 0.25f;
//const GLfloat ZOOM = 45.0f;


class Camera
{
public:
	

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	GLfloat pitch = 0.0f;
	/*GLfloat lastX = App->window->width / 2.0;
	GLfloat lastY = App->window->height / 2.0;*/
	GLfloat lastX = SCREEN_WIDTH * SCREEN_SIZE / 2.0;
	GLfloat lastY = SCREEN_HEIGHT * SCREEN_SIZE / 2.0;
	GLfloat fov = 45.0f;
	iPoint mousePosition = { 0,0 };
	Camera() {};
	~Camera() {};

	

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
	
	void scroll_movement()
	{
		double yoffset = App->input->GetMouseWheelMotion().x * 6000 * App->deltaTime;

		if (fov >= 1.0f && fov <= 45.0f)
			fov -= yoffset*App->deltaTime;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;
	}

	glm::mat4 getViewMatrix() 
	{
		return  glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	glm::mat4 getProjectionMatrix() 
	{
		return  glm::perspective(fov, (GLfloat)App->window->width / (GLfloat)App->window->height, 0.1f, 100.0f);
	}
};


#endif