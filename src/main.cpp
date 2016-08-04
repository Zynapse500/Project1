//Standard includes
#include <stdio.h>
#include <conio.h>

//OpenGL includes
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	printf("Hello World!\n");


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800,600, "LearnOpenGL", nullptr, nullptr);
	if(window == nullptr)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	
	//glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);


	while(!glfwWindowShouldClose(window))
	{
		//Check and call events
		glfwPollEvents();

		//Rendering commands here
		glClearColor(0.2,0.3,0.3,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Swap the buffers
		glfwSwapBuffers(window);
	}


	glfwTerminate();


	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}