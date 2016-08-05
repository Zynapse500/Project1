//Standard includes
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>

//My includes
#include "Shader.h"

//OpenGL includes
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//Soil
#include <SOIL.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

float mixValue = 0.5;

int main()
{
	printf("Hello World!\n");

	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));



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
	
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	//Shader
	Shader ourShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");


	//Vertices
	GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
	};  

	//Texture

	int imageWidth1, imageHeight1;
	unsigned char* image1 = SOIL_load_image("res/container.jpg", &imageWidth1, &imageHeight1, 0, SOIL_LOAD_RGB);

	int imageWidth2, imageHeight2;
	unsigned char* image2 = SOIL_load_image("res/awesomeface.jpg", &imageWidth2, &imageHeight2, 0, SOIL_LOAD_RGB);

	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth1, imageHeight1, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);

	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth2, imageHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Object
	GLuint VBO, EBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Drawing Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Game loop
	while(!glfwWindowShouldClose(window))
	{
		//Check and call events
		glfwPollEvents();

		//Rendering commands here
		glClearColor(0.2,0.3,0.3,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate the shader
		ourShader.Use();


		//enable textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);


		//Set the mix value for the textures
		glUniform1f(glGetUniformLocation(ourShader.Program, "mixValue"), mixValue);


		//transform the object
		GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


		//draw the object
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Swap the buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1;
		if(mixValue >= 1.0)
			mixValue = 1.0;
	}

	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1;
		if(mixValue <= 0.0)
			mixValue = 0.0;
	}

	
}

std::string getFromFile(std::string path)
{
	std::string ret;
	std::ifstream ifs(path.c_str());
	if(ifs)
	{
		std::string line;
		while(getline(ifs, line))
		{
			ret = ret + line + "\n";
		}
		ifs.close();
	}
	else
	{
		return "";
	}
	return ret;
}	