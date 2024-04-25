#include "Chunk.h"

Chunk::Chunk(glm::vec2 pos)
    : position(pos)
{
    SimplexNoise simplexNoise;

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_LENGTH; z++)
            {
                int index = x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);

                float worldX = position.x * CHUNK_WIDTH + x;
                float worldZ = position.y * CHUNK_WIDTH + z;

                float noiseVal = simplexNoise.fractal(4, worldX * 0.01, worldZ * 0.01);
                int height = static_cast<int>((noiseVal + 1.0) * 32 / 2);

                if (y < height)
                    blocks[index] = 1;
                else
                    blocks[index] = 0;
            }
        }
	}
    
    GenerateMesh();
    
	std::cout << meshVertexPositions.size() << std::endl;
}

Chunk::~Chunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

void Chunk::DrawChunk()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
}

bool Chunk::IsBlockHidden(int x, int y, int z, int face) const
{
    // Calculate the index of the current block
    int index = x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);

    // Get the neighboring block indices based on the face
    int nx = x, ny = y, nz = z; // Neighbor coordinates
    switch (face)
    {
    case 0: // Front Face
        nz++;
        break;
    case 1: // Back Face
        nz--;
        break;
    case 2: // Right Face
        nx++;
        break;
    case 3: // Left Face
        nx--;
        break;
    case 4: // Top Face
        ny++;
        break;
    case 5: // Bottom Face
        ny--;
        break;
    default:
        break;
    }

    // Check if the neighboring block is out of bounds or empty
    if (nx < 0 || nx >= CHUNK_WIDTH || ny < 0 || ny >= CHUNK_HEIGHT || nz < 0 || nz >= CHUNK_LENGTH)
        return true; // Out of bounds
    else
    {
        // Calculate the index of the neighboring block
        int nIndex = nx + CHUNK_WIDTH * (ny + CHUNK_HEIGHT * nz);
        // Check if the neighboring block is empty
        return blocks[nIndex] == 0;
    }
}


void Chunk::DeleteChunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

void Chunk::GenerateMesh()
{
    meshVertexPositions.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 24);
    meshTexCoords.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 24);
    meshShadingValues.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 24);
    meshIndices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 36);

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                int index = x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
                if (blocks[index] == 1)
                {
                    float worldX = position.x * CHUNK_WIDTH + x;
                    float worldZ = position.y * CHUNK_WIDTH + z;

                    // Generate mesh data for each block
                    float startX = position.x * CHUNK_WIDTH;
                    float startY = 0.0;
                    float startZ = position.y * CHUNK_LENGTH;
                
                    // Front Face
                    if (IsBlockHidden(x, y, z, 0))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z + 1,
                            startX + x, startY + y + 1, startZ + z + 1,
                            startX + x + 1, startY + y + 1, startZ + z + 1,
                            startX + x + 1, startY + y, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                        });
                    }
                    // Back Face
                    if (IsBlockHidden(x, y, z, 1))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z,
                            startX + x + 1, startY + y, startZ + z,
                            startX + x + 1, startY + y + 1, startZ + z,
                            startX + x, startY + y + 1, startZ + z,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                        });
                    }
                    // Right Face
                    if (IsBlockHidden(x, y, z, 2))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x + 1, startY + y, startZ + z + 1, // Vertex 0
                            startX + x + 1, startY + y + 1, startZ + z + 1, // Vertex 1
                            startX + x + 1, startY + y + 1, startZ + z, // Vertex 2
                            startX + x + 1, startY + y, startZ + z, // Vertex 3
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                        });
                    }
                    // Left Face
                    if (IsBlockHidden(x, y, z, 3))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z,
                            startX + x, startY + y + 1, startZ + z,
                            startX + x, startY + y + 1, startZ + z + 1,
                            startX + x, startY + y, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                        });
                    }
                    // Top Face
                    if (IsBlockHidden(x, y, z, 4))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y + 1, startZ + z,
                            startX + x + 1, startY + y + 1, startZ + z,
                            startX + x + 1, startY + y + 1, startZ + z + 1,
                            startX + x, startY + y + 1, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {        
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                        });
                    }
                    // Bottom Face
                    if (IsBlockHidden(x, y, z, 5))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z, // Vertex 0
                            startX + x, startY + y, startZ + z + 1, // Vertex 1
                            startX + x + 1, startY + y, startZ + z + 1, // Vertex 2
                            startX + x + 1, startY + y, startZ + z, // Vertex 3
                        });

                        meshTexCoords.insert(meshTexCoords.end(), {
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f
                        });

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f
                        });
                    }

                // Indices
                GLuint baseIndex = meshVertexPositions.size() / 3 - 24; // Adjust baseIndex for the current block
                meshIndices.insert(meshIndices.end(), {
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
    
    vao.Bind();
    
    VBO vertVBO(meshVertexPositions);
    VBO texVBO(meshTexCoords);
    VBO shadingVBO(meshShadingValues);
    
    EBO ebo(meshIndices);
    
    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();

    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}