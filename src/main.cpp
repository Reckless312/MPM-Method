#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

int main() 
{
	glfwInit();

	const int majorVersion = 3;
	const int minorVersion = 3;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int windowWidth = 800;
	const int windowHeight = 600;
	const char* windowTitle = "OpenGL Window";
	GLFWmonitor* monitor = NULL;
	GLFWwindow* sharedWindow = NULL;


	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, monitor, sharedWindow);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	const int bottomLeftX = 0;
	const int bottomLeftY = 0;

	glViewport(bottomLeftX, bottomLeftY, windowWidth, windowHeight);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	
	glfwTerminate();

	return 0;
}