#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Tree
{
public:
    Tree(glm::vec3 spawnPos);

    void GenerateTrunk();
    void GenerateLeaves();
    void GenerateBuffers();
    void Render();

private:
    std::vector<GLfloat> treeVertices;
    std::vector<GLfloat> treeTexCoords;
    std::vector<GLfloat> treeShading;
    std::vector<GLuint> treeIndices;

    int generateRandomSeed();

    int blocks[64];

    int height = 4;

    glm::vec3 position;

    VAO vao;
};