#ifndef __READ_FILE_H_
#define __READ_FILE_H_
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Glew/include/GL/glew.h"

class ReadFileShader
{
public:

	ReadFileShader() 
	{
	}

	
	// Constructor generates the shader on the fly
	void getShaders(const GLchar* vertexPath, const GLchar* fragmentPath, std::string &vertex, std::string &fragment)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		vertex = vertexCode;
		fragment = fragmentCode;
		}
	};





#endif // !__READ_FILE_H
