#include "Shader.h"

std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);

    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* filename, GLenum type) {
    std::string shaderCode = get_file_contents(filename);

    const char* shaderSource = shaderCode.c_str();

    ID = glCreateShader(type);
    glShaderSource(ID, 1, &shaderSource, NULL);
    glCompileShader(ID);
    compileErrors();
}

void Shader::compileErrors() {
    GLint hasCompiled;

    char infoLog[1024];

    glGetShaderiv(ID, GL_COMPILE_STATUS, &hasCompiled);

    if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(ID, sizeof(infoLog), NULL, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR: " << "\n" << infoLog << std::endl;
    }
}