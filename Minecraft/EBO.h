#pragma once

#include <glad/glad.h>
#include <vector>

class EBO
{
public:

	EBO(std::vector<GLuint> indices);

	GLuint ID;

	void Bind();
	void Unbind();
	void Delete();
};
