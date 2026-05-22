#pragma once

#include <glad/glad.h>
#include "Shader.h"

class ShaderProgram{
public:
    GLuint ID;

    ShaderProgram();

    void Attach(Shader& shader);
    void Link();
    void Activate();
    void Delete();

private:
    void compileErrors();
};