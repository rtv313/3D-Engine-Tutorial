#ifndef  __TUTORIAL_5_H_
#define  __TUTORIAL_5_H_


#include "Glew/include/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/vec3.hpp" 
#include <stdio.h>
#include <string>
#include "ReadFile.h"


class TriangleWithShaderUniformVar
{
private:
	ReadFileShader ReadFile;
	GLuint shaderProgram;
	GLuint VBO, VAO, EBO;
	const char* pVSFileName = "../shader05.vs";
	const char* pFSFileName = "../shader.fs";
	GLuint gScaleLocation;
	float Scale = 0.0f;

public:

	TriangleWithShaderUniformVar()
	{
		CreateVertexBuffer();
		CreateShaders();
	}

	~TriangleWithShaderUniformVar()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void draw()
	{
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Uniform Variable
		Scale += 0.001f;
		glUniform1f(gScaleLocation, sinf(Scale));

		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}


private:
	void CreateVertexBuffer()
	{
		GLfloat vertices[] = {
			0.5f,  0.5f, 0.0f,  // Top Right
			0.5f, -0.5f, 0.0f,  // Bottom Right
			-0.5f, -0.5f, 0.0f,  // Bottom Left

		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,  // First Triangle

		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	}

	void CreateShaders()
	{
		std::string getVertexShaderSource;
		std::string getFragmentShaderSource;

		ReadFile.getShaders(pVSFileName, pFSFileName, getVertexShaderSource, getFragmentShaderSource);

		//Convert from string to char
		GLchar* vertexShaderSource = new char[getVertexShaderSource.length() + 1];
		strcpy(vertexShaderSource, getVertexShaderSource.c_str());

		GLchar* fragmentShaderSource = new char[getFragmentShaderSource.length() + 1];
		strcpy(fragmentShaderSource, getFragmentShaderSource.c_str());

		// Build and compile our shader program
		// Vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// Check for compile time errors
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// Check for compile time errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		//Set Uniform Variable
		gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");
		assert(gScaleLocation != 0xFFFFFFFF);

		//We delete this because we dont need anymore
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		delete vertexShaderSource;
		delete fragmentShaderSource;
	}
};

#endif // ! __TUTORIAL_5_H