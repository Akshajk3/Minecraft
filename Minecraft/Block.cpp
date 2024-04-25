#include "Block.h"

BlockType::BlockType(glm::vec3 position)
    : vertVBO(numbers.vertices), texVBO(numbers.texCoords), shadingVBO(numbers.shadingValues), ebo(numbers.indices)
{
    vertexPositions = numbers.vertices;
    texCoords = numbers.texCoords;
    shadingValues = numbers.shadingValues;
    
    for (int i = 0; i < vertexPositions.size(); i+=3)
    {
        vertexPositions[i] += position.x;
        vertexPositions[i + 1] += position.y;
        vertexPositions[i + 2] += position.z;
    }
    
    vao.Bind();
    
    vertVBO = VBO(vertexPositions);
    texVBO = VBO(texCoords);
    shadingVBO = VBO(shadingValues);
    
    ebo = EBO(numbers.indices);
    
    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();
}

BlockType::~BlockType()
{
    vertexPositions.clear();
    vertexPositions.shrink_to_fit(); // Reduce the capacity to match the size
    texCoords.clear();
    texCoords.shrink_to_fit();
    shadingValues.clear();
    shadingValues.shrink_to_fit();
    vao.Delete();
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}

void BlockType::Draw()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, numbers.indices.size(), GL_UNSIGNED_INT, 0);
}

void BlockType::Delete() {
    vertexPositions.clear();
    vertexPositions.shrink_to_fit(); // Reduce the capacity to match the size
    texCoords.clear();
    texCoords.shrink_to_fit();
    shadingValues.clear();
    shadingValues.shrink_to_fit();
    vao.Delete();
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}


std::vector<GLfloat> BlockType::getVertexPositions()
{
    return vertexPositions;
}

std::vector<GLfloat> BlockType::getTexCoords()
{
    return texCoords;
}

std::vector<GLfloat> BlockType::getShadingValues()
{
    return shadingValues;
}
