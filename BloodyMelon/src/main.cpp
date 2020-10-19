//*********		include starts		*********
	// VS include
#include <iostream>
	// OpenGL externals include
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//*********		include ends		*********


int main() {
	// Initialize GLFW
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to initialize Glad" << std::endl;
		return 1;
	}
	// Create a new GLFW window
	GLFWwindow* window = glfwCreateWindow(300, 300, "Hello!", nullptr, nullptr);
	// We want GL commands to be executed for our window, so we make our window's context the current one

	glfwMakeContextCurrent(window);

	// Let glad know what function loader we are using (will call gl commands via glfw)
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		std::cout << "Failed to initialize Glad" << std::endl;
		return 2;
	}
	// Display our GPU and OpenGL version
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Run as long as the window is open
	while (!glfwWindowShouldClose(window)) {
		// Poll for events from windows (clicks, keypressed, closing, all that)
		glfwPollEvents();
		// Clear our screen every frame
		glClearColor(0.1f, 0.7f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Present our image to windows
		glfwSwapBuffers(window);
	}
	return 0;

	// Test 5


}