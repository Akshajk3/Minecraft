# pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

class VBO
{
public:
	VBO(std::vector<GLfloat> vertices);
	
	GLuint ID;

	void Bind();
	void Unbind();
	void Delete();
};
