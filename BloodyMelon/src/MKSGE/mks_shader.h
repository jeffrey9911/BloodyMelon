#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class mks_shader
{
private:
	void checkError(GLuint shaderID, std::string checkType);
public:
	GLuint shaderID;
	mks_shader(std::string vShaderPath, std::string fShaderPath, std::string gShaderPath = "");

	void useShader();
};

