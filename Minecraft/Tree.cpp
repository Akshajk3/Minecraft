#include "Tree.h"

Tree::Tree(glm::vec3 spawnPos)
    : position(spawnPos)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(3, 6);

    height = distr(gen);

    GenerateTrunk();
    GenerateLeaves();
    GenerateBuffers();
}

void Tree::GenerateTrunk()
{

    std::vector<GLfloat> sideTexCoords = {
        0.75f, 0.0f,
        0.75f, 0.25f,
        1.0f, 0.25f,
        1.0f, 0.0f 
    };
    
    std::vector<GLfloat> backTexCoords = {
        0.75f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.25f,
        0.75f, 0.25f
    };
    std::vector<GLfloat> topTexCoords = {
        0.5f, 0.0f,
        0.5f, 0.25f,
        0.75f, 0.25f,
        0.75f, 0.0f 
    };

    for (int y = 0; y < height; y++)
    {
        for (int face = 0; face < 6; face++)
        {
            // Front Face
            if (face == 0)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x,     position.y + y,     position.z + 1,
                    position.x,     position.y + y + 1, position.z + 1,
                    position.x + 1, position.y + y + 1, position.z + 1,
                    position.x + 1, position.y + y,     position.z + 1,
                });

                treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                treeShading.insert(treeShading.end(), {
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                });

            }
            
            // Back Face
            if (face == 1)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x,     position.y + y,     position.z,             // Vertex 0
                    position.x + 1, position.y + y,     position.z,         // Vertex 1
                    position.x + 1, position.y + y + 1, position.z,     // Vertex 2
                    position.x,     position.y + y + 1, position.z,         // Vertex 3
                });

                treeTexCoords.insert(treeTexCoords.end(), backTexCoords.begin(), backTexCoords.end());

                treeShading.insert(treeShading.end(), {
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                    0.6f, 0.6f, 0.6f, 0.6f,
                });

            }

            // Right Face
            if (face == 2)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x + 1, position.y + y,     position.z + 1, // Vertex 0
                    position.x + 1, position.y + y + 1, position.z + 1, // Vertex 1
                    position.x + 1, position.y + y + 1, position.z, // Vertex 2
                    position.x + 1, position.y + y,     position.z, // Vertex 3
                });

                treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                treeShading.insert(treeShading.end(), {
                    0.4f, 0.4f, 0.4f, 0.4f,
                    0.4f, 0.4f, 0.4f, 0.4f,
                    0.4f, 0.4f, 0.4f, 0.4f,
                    0.4f, 0.4f, 0.4f, 0.4f,
                });
            }
            // Left Face
            if (face == 3)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x, position.y + y,     position.z,
                    position.x, position.y + y + 1, position.z,
                    position.x, position.y + y + 1, position.z + 1,
                    position.x, position.y + y,     position.z + 1,
                });

                treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                treeShading.insert(treeShading.end(), {
                    1.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 1.0f,
                });
            }
            // Top Face
            if (face == 4)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x,     position.y + y + 1, position.z,
                    position.x + 1, position.y + y + 1, position.z,
                    position.x + 1, position.y + y + 1, position.z + 1,
                    position.x,     position.y + y + 1, position.z + 1,
                });

                treeTexCoords.insert(treeTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

                treeShading.insert(treeShading.end(), {        
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f,
                });
            }
            // Bottom Face
            if (face == 5)
            {
                treeVertices.insert(treeVertices.end(), {
                    position.x, position.y + y, position.z, // Vertex 0
                    position.x, position.y + y, position.z + 1, // Vertex 1
                    position.x + 1, position.y + y, position.z + 1, // Vertex 2
                    position.x + 1, position.y + y, position.z, // Vertex 3
                });

                treeTexCoords.insert(treeTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

                treeShading.insert(treeShading.end(), {
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f,
                    0.8f, 0.8f, 0.8f, 0.8f
                });
            }

            // Indices
            GLuint baseIndex = treeVertices.size() / 3 - 24; // Adjust baseIndex for the current block
            treeIndices.insert(treeIndices.end(), {
                baseIndex, baseIndex + 1, baseIndex + 2, baseIndex + 2, baseIndex + 3, baseIndex,
                baseIndex + 4, baseIndex + 5, baseIndex + 6, baseIndex + 6, baseIndex + 7, baseIndex + 4,
                baseIndex + 8, baseIndex + 9, baseIndex + 10, baseIndex + 10, baseIndex + 11, baseIndex + 8,
                baseIndex + 12, baseIndex + 13, baseIndex + 14, baseIndex + 14, baseIndex + 15, baseIndex + 12,
                baseIndex + 16, baseIndex + 17, baseIndex + 18, baseIndex + 18, baseIndex + 19, baseIndex + 16,
                baseIndex + 20, baseIndex + 21, baseIndex + 22, baseIndex + 22, baseIndex + 23, baseIndex + 20
            });
        }
    }
}

void Tree::GenerateLeaves()
{
    int seed = generateRandomSeed();
    std::srand(seed);

    std::vector<GLfloat> sideTexCoords = {
        0.5f, 0.25f,
        0.5f, 0.5f,
        0.75f, 0.5f,
        0.75f, 0.25f
    };
    std::vector<GLfloat> backTexCoords = {
        0.5f, 0.25f,
        0.75f, 0.25f,
        0.75f, 0.5f,
        0.5f, 0.5f
    };
    std::vector<GLfloat> topTexCoords = {
        0.5f, 0.25f,
        0.5f, 0.5f,
        0.75f, 0.5f,
        0.75f, 0.25f
    };

    for (int y = 0; y < 3; y++)
    {
        for (int x = -2 + y; x <= 2 - y; x++)
        {
            for (int z = -2 + y; z <= 2 - y; z++)
            {
                for (int face = 0; face < 6; face++)
                {
                    if (true)
                    {
                        if (face == 0)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x,     position.y + height - 2 + y,     position.z + z + 1,
                                position.x + x,     position.y + height - 2 + y + 1, position.z + z + 1,
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z + 1,
                                position.x + x + 1, position.y + height - 2 + y,     position.z + z + 1,
                            });

                            treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                            treeShading.insert(treeShading.end(), {
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                            });
                        }
                        // Back Face
                        if (face == 1)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x,     position.y + height - 2 + y,     position.z + z,             // Vertex 0
                                position.x + x + 1, position.y + height - 2 + y,     position.z + z,         // Vertex 1
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z,     // Vertex 2
                                position.x + x,     position.y + height - 2 + y + 1, position.z + z,         // Vertex 3
                            });

                            treeTexCoords.insert(treeTexCoords.end(), backTexCoords.begin(), backTexCoords.end());

                            treeShading.insert(treeShading.end(), {
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                                0.6f, 0.6f, 0.6f, 0.6f,
                            });

                        }

                        // Right Face
                        if (face == 2)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x + 1, position.y + height - 2 + y,     position.z + z + 1, // Vertex 0
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z + 1, // Vertex 1
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z, // Vertex 2
                                position.x + x + 1, position.y + height - 2 + y,     position.z + z, // Vertex 3
                            });

                            treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                            treeShading.insert(treeShading.end(), {
                                0.4f, 0.4f, 0.4f, 0.4f,
                                0.4f, 0.4f, 0.4f, 0.4f,
                                0.4f, 0.4f, 0.4f, 0.4f,
                                0.4f, 0.4f, 0.4f, 0.4f,
                            });
                        }
                        // Left Face
                        if (face == 3)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x, position.y + height - 2 + y,     position.z + z,
                                position.x + x, position.y + height - 2 + y + 1, position.z + z,
                                position.x + x, position.y + height - 2 + y + 1, position.z + z + 1,
                                position.x + x, position.y + height - 2 + y,     position.z + z + 1,
                            });

                            treeTexCoords.insert(treeTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                            treeShading.insert(treeShading.end(), {
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                            });
                        }
                        // Top Face
                        if (face == 4)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x,     position.y + height - 2 + y + 1, position.z + z,
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z,
                                position.x + x + 1, position.y + height - 2 + y + 1, position.z + z + 1,
                                position.x + x,     position.y + height - 2 + y + 1, position.z + z + 1,
                            });

                            treeTexCoords.insert(treeTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

                            treeShading.insert(treeShading.end(), {        
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f,
                            });
                        }
                        // Bottom Face
                        if (face == 5)
                        {
                            treeVertices.insert(treeVertices.end(), {
                                position.x + x,     position.y + height - 2 + y, position.z + z, // Vertex 0
                                position.x + x,     position.y + height - 2 + y, position.z + z + 1, // Vertex 1
                                position.x + x + 1, position.y + height - 2 + y, position.z + z + 1, // Vertex 2
                                position.x + x + 1, position.y + height - 2 + y, position.z + z, // Vertex 3
                            });

                            treeTexCoords.insert(treeTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

                            treeShading.insert(treeShading.end(), {
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f,
                                0.8f, 0.8f, 0.8f, 0.8f
                            });
                        }

                        // Indices
                        GLuint baseIndex = treeVertices.size() / 3 - 24; // Adjust baseIndex for the current block
                        treeIndices.insert(treeIndices.end(), {
                            baseIndex, baseIndex + 1, baseIndex + 2, baseIndex + 2, baseIndex + 3, baseIndex,
                            baseIndex + 4, baseIndex + 5, baseIndex + 6, baseIndex + 6, baseIndex + 7, baseIndex + 4,
                            baseIndex + 8, baseIndex + 9, baseIndex + 10, baseIndex + 10, baseIndex + 11, baseIndex + 8,
                            baseIndex + 12, baseIndex + 13, baseIndex + 14, baseIndex + 14, baseIndex + 15, baseIndex + 12,
                            baseIndex + 16, baseIndex + 17, baseIndex + 18, baseIndex + 18, baseIndex + 19, baseIndex + 16,
                            baseIndex + 20, baseIndex + 21, baseIndex + 22, baseIndex + 22, baseIndex + 23, baseIndex + 20
                        });
                    }
                }
            }
        }
    }
}



void Tree::GenerateBuffers()
{
    vao.Bind();
    
    VBO vertVBO(treeVertices);
    VBO texVBO(treeTexCoords);
    VBO shadingVBO(treeShading);
    EBO ebo(treeIndices);

    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();
}

void Tree::Render()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, treeIndices.size(), GL_UNSIGNED_INT, 0);
}

int Tree::generateRandomSeed()
{
    return static_cast<int>(std::time(nullptr));
}