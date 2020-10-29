// Include list
// ************
#include "mks_GE.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>

// File path generator
// *******************
std::string mks_GE::genPath(std::string filePath)
{
	std::string returning;
	returning = genRoot + "/" + filePath;
	std::replace(returning.begin(), returning.end(), '/', '\\');
	std::ifstream ifReadable(returning);
	if (!ifReadable) {
		std::cout << std::endl << "[¡Á] - Failed to read file: " << returning;
		ifReadable.close();
		exit(1);
	}
	else {
		std::cout << std::endl << "[¡Ì] - Succeeded to read file: " << returning;
		ifReadable.close();
		return returning;
	}
}

// Input Processor per loop
// ************************
void mks_GE::inputProcessPerLoop(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // ESC down

	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // W down

	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // A down

	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // S down

	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // D down

	}

	
}
