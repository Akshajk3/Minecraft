#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include <VBO.h>
#include "EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};


const unsigned int width = 800;
const unsigned int height = 600;

int main()
{
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	if (window == nullptr) {
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "Failed to Initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	Shader vertexShader("../../Minecraft V2.0/shaders/vert.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("../../Minecraft V2.0/shaders/frag.glsl", GL_FRAGMENT_SHADER);

	ShaderProgram shaderProgram;

	shaderProgram.Attach(vertexShader);
	shaderProgram.Attach(fragmentShader);

	shaderProgram.Link();

	VAO VAO1;
	VAO1.Bind();

	VBO vert(vertices, sizeof(vertices));

	EBO ind(indices, sizeof(indices));

	VAO1.LinkVBO(vert, 0);
	VAO1.Unbind();
	vert.Unbind();
	ind.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}