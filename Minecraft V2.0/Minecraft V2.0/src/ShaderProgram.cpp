#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    ID = glCreateProgram();
}

void ShaderProgram::Attach(Shader& shader) {
    glAttachShader(ID, shader.ID);
    glDeleteShader(shader.ID);
}

void ShaderProgram::Link() {
    glLinkProgram(ID);
}

void ShaderProgram::Activate() {
    glUseProgram(ID);
}

void ShaderProgram::Delete() {
    glDeleteProgram(ID);
}