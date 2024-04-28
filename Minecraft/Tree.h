#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Tree
{
public:
    Tree(glm::vec3 spawnPos);

    void GenerateMesh();
    void Render();

private:
    std::vector<GLfloat> treeVertices;
    std::vector<GLfloat> treeTexCoords;
    std::vector<GLfloat> treeShading;
    std::vector<GLuint> treeIndices;

    int blocks[64];

    glm::vec3 position;

    VAO vao;
};