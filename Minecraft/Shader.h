#pragma once

#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	
	GLuint ID;

	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};