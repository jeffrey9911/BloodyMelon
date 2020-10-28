//*********		include starts		*********
	// VS include
#include "mks_shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
	// OpenGL externals include
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//*********		include ends		*********


void mks_shader::checkError(GLuint shaderID, std::string checkType)
{
	GLint ifSuccess;
	GLchar errorLog[1024];
	if (checkType != "LINK") { // Program Link Check
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &ifSuccess);
		if(!ifSuccess) {
			glGetShaderInfoLog(shaderID, 1024, NULL, errorLog);
			std::cout << std::endl << "[X] - Failed to compile TYPE:" << checkType << ":" << std::endl << errorLog;
		}
		else { std::cout << std::endl << "[¡Ì] - Succeeded to compile: " << shaderID; }
	}
	else { // Shader Compile Check
		glGetProgramiv(shaderID, GL_LINK_STATUS, &ifSuccess);
		if (!ifSuccess) {
			glGetShaderInfoLog(shaderID, 1024, NULL, errorLog);
			std::cout << std::endl << "[X] - Failed to link: " << std::endl << errorLog;
		}
		else { std::cout << std::endl << "[¡Ì] - Succeeded to link: " << shaderID; }
	}
}

mks_shader::mks_shader(std::string vShaderPath, std::string fShaderPath, std::string gShaderPath)
{
	std::string vShaderCode;
	std::string fShaderCode;
	std::string gShaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vShaderPath);
		fShaderFile.open(fShaderPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();

		// Check G shader
		if (gShaderPath != "") {
			gShaderFile.open(gShaderPath);

			std::stringstream gShaderStream;

			gShaderStream << gShaderFile.rdbuf();

			gShaderFile.close();

			gShaderCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure& exception)
	{
		std::cout << std::endl << "[X] - Filed to load shaders: " << exception.what();
	}
	const char* vShaderCodePtr = vShaderCode.c_str();
	const char* fShaderCodePtr = fShaderCode.c_str();

	GLuint vShaderID, fShaderID;

	// Process shaders
	// ***************
	vShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderID, 1, &vShaderCodePtr, NULL);
	glCompileShader(vShaderID);
	checkError(vShaderID, "VERTEX");

	fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderID, 1, &fShaderCodePtr, NULL);
	glCompileShader(fShaderID);
	checkError(fShaderID, "FRAGMENT");

	// Check G shader
	GLuint gShaderID;
	if (gShaderPath != "") {
		const char* gShaderCodePtr = gShaderCode.c_str();
		gShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShaderID, 1, &gShaderCodePtr, NULL);
		glCompileShader(gShaderID);
		checkError(gShaderID, "GEOMETRY");
	}

	// Link shaders
	// ************
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vShaderID);
	glAttachShader(shaderID, fShaderID);
	if (gShaderPath != "") { glAttachShader(shaderID, gShaderID); }
	glLinkProgram(shaderID);
	checkError(shaderID, "LINK");

	// Process RAM
	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);
	if (gShaderPath != "") { glDeleteShader(gShaderID); }
}

// Using the shaders
// *****************
void mks_shader::useShader()
{
	glUseProgram(shaderID);
}


