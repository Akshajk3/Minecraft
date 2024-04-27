#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

class Tree
{
public:
    Tree(glm::vec3 spawnPos);

private:
    std::vector<GLfloat> treeVertices;
    std::vector<GLfloat> treeTexCoords;
    std::vector<GLfloat> teeShading;
    std::vector<GLfloat> treeIndices;

    
};