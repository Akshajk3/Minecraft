#include "Tree.h"

Tree::Tree(glm::vec3 spawnPos)
    : position(spawnPos)
{
    for (int y = 0; y < 4; y++)
    {
        int index = 
    }

    GenerateMesh();
}

void Tree::GenerateMesh()
{

}

void Tree::Render()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, treeIndices.size(), GL_UNSIGNED_INT, 0);
}