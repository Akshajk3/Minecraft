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
    compileErrors();
}

void ShaderProgram::Activate() {
    glUseProgram(ID);
}

void ShaderProgram::Delete() {
    glDeleteProgram(ID);
}

void ShaderProgram::compileErrors() {
    GLint hasCompiled;

    char infoLog[1024];

    glGetShaderiv(ID, GL_LINK_STATUS, &hasCompiled);

    if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(ID, sizeof(infoLog), NULL, infoLog);
        std::cout << "SHADER_LINKING_ERROR: " << "\n" << infoLog << std::endl;
    }
}