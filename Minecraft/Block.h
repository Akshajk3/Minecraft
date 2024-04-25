#pragma once 

#include <unordered_map>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Numbers.h"
#include "Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

class BlockType
{
public:
    BlockType(glm::vec3 position);
    ~BlockType();
    
    void Draw();
    void Delete();

    std::vector<GLfloat> getVertexPositions();
    std::vector<GLfloat> getTexCoords();
    std::vector<GLfloat> getShadingValues();

private:
    std::string name;
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> shadingValues;

    Numbers numbers;
    VAO vao;
    VBO vertVBO;
    VBO texVBO;
    VBO shadingVBO;
    EBO ebo;
};
