#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class Shader {
public:
    GLuint ID;
    Shader(const char* shaderFile, GLenum type);
};