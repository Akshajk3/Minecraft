#include "Chunk.h"

Chunk::Chunk(glm::vec2 pos, SimplexNoise& Snoise, int waterLevel)
    : position(pos), noise(Snoise)
{
    int numThreads = std::thread::hardware_concurrency();
    int sectionHeight = CHUNK_HEIGHT / numThreads;

    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    for (int i = 0; i < numThreads; ++i) {
        int startY = i * sectionHeight;
        int endY = (i == numThreads - 1) ? CHUNK_HEIGHT : startY + sectionHeight;

        threads.emplace_back([this, startY, endY, &Snoise, waterLevel]() {
            auto threadStart = std::chrono::high_resolution_clock::now(); // Start thread timing
            GenerateChunkSection(*this, startY, endY, noise, waterLevel); // Pass the chunk object
            auto threadEnd = std::chrono::high_resolution_clock::now(); // End thread timing
            std::chrono::duration<double> threadDuration = threadEnd - threadStart;
            //std::cout << "Thread finished in " << threadDuration.count() << " seconds." << std::endl;
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> duration = end - start;
    //std::cout << "Chunk generation finished in " << duration.count() << " seconds." << std::endl;

    GenerateMesh();
    
    //std::cout << meshVertexPositions.size() << std::endl;
}

// Modify GenerateChunkSection to take Chunk as its first argument
void Chunk::GenerateChunkSection(Chunk& chunk, int startY, int endY, SimplexNoise& noise, int waterLevel) {
    // Generation logic remains the same
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = startY; y < endY; y++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                int index = x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
                float worldX = chunk.position.x * CHUNK_WIDTH + x;
                float worldZ = chunk.position.y * CHUNK_WIDTH + z;
                float noiseVal = noise.fractal(4, worldX * 0.01, worldZ * 0.01);
                int height = static_cast<int>((noiseVal + 1.0) * 32 / 2);

                if (y < height)
                    chunk.blocks[index] = 1; // or any solid block
                else if (y < waterLevel)
                    chunk.blocks[index] = 2; // water
                else
                    chunk.blocks[index] = 0; // air
            }
        }
    }
}

Chunk::~Chunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
    trees.clear();
}

void Chunk::DrawChunk()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
    for (auto& tree : trees)
    {
        tree.Render();
    }
}

bool Chunk::IsBlockHidden(int x, int y, int z, int face, bool water) const
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
        if (water)
            return blocks[nIndex] != 2;
        else
            return blocks[nIndex] != 1;
    }
}


void Chunk::DeleteChunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
    trees.clear();
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
                float worldX = position.x * CHUNK_WIDTH + x;
                float worldZ = position.y * CHUNK_WIDTH + z;

                // Generate mesh data for each block
                float startX = position.x * CHUNK_WIDTH;
                float startY = 0.0;
                float startZ = position.y * CHUNK_LENGTH;

                float noiseVal = noise.fractal(4, worldX * 0.01, worldZ * 0.01);
                int height = static_cast<int>((noiseVal + 1.0) * 32 / 2);
                
                if (x == 0 && y == height && z == 0 && blocks[index] == 0)
                {
                    trees.push_back(Tree(glm::vec3(startX, y, startZ)));
                }
                
                if (blocks[index] != 0)
                {
                    std::vector<GLfloat> sideTexCoords;
                    std::vector<GLfloat> backTexCoords;
                    std::vector<GLfloat> topTexCoords;
                    bool water = false;

                    switch (blocks[index])
                    {
                    case 1:
                        sideTexCoords = {
                            0.25f, 0.0f,
                            0.25f, 0.5f,
                            0.5f, 0.5f,
                            0.5f, 0.0f 
                        };
                        
                        backTexCoords = {
                            0.25f, 0.0f,
                            0.5f, 0.0f,
                            0.5f, 0.5f,
                            0.25f, 0.5f
                        };
                        topTexCoords = {
                            0.0f, 0.0f,
                            0.0f, 0.5f,
                            0.25f, 0.5f,
                            0.25f, 0.0f 
                        };
                        break;
                    case 2:
                        sideTexCoords = {
                            0.25f, 0.5f,
                            0.5f, 0.5f,
                            0.5f, 1.0f,
                            0.25f, 1.0f 
                        };
                        backTexCoords = sideTexCoords;
                        topTexCoords = sideTexCoords;

                        water = true;
                        break;
                    default:
                        break;
                    }

                    // Front Face
                    if (IsBlockHidden(x, y, z, 0, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z + 1,
                            startX + x, startY + y + 1, startZ + z + 1,
                            startX + x + 1, startY + y + 1, startZ + z + 1,
                            startX + x + 1, startY + y, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                        });
                    }
                    // Back Face
                    if (IsBlockHidden(x, y, z, 1, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z,             // Vertex 0
                            startX + x + 1, startY + y, startZ + z,         // Vertex 1
                            startX + x + 1, startY + y + 1, startZ + z,     // Vertex 2
                            startX + x, startY + y + 1, startZ + z,         // Vertex 3
                        });

                        meshTexCoords.insert(meshTexCoords.end(), backTexCoords.begin(), backTexCoords.end());

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                            0.6f, 0.6f, 0.6f, 0.6f,
                        });
                    }
                    // Right Face
                    if (IsBlockHidden(x, y, z, 2, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x + 1, startY + y, startZ + z + 1, // Vertex 0
                            startX + x + 1, startY + y + 1, startZ + z + 1, // Vertex 1
                            startX + x + 1, startY + y + 1, startZ + z, // Vertex 2
                            startX + x + 1, startY + y, startZ + z, // Vertex 3
                        });

                        meshTexCoords.insert(meshTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                        meshShadingValues.insert(meshShadingValues.end(), {
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                            0.4f, 0.4f, 0.4f, 0.4f,
                        });
                    }
                    // Left Face
                    if (IsBlockHidden(x, y, z, 3, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z,
                            startX + x, startY + y + 1, startZ + z,
                            startX + x, startY + y + 1, startZ + z + 1,
                            startX + x, startY + y, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), sideTexCoords.begin(), sideTexCoords.end());

                        meshShadingValues.insert(meshShadingValues.end(), {
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                        });
                    }
                    // Top Face
                    if (IsBlockHidden(x, y, z, 4, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y + 1, startZ + z,
                            startX + x + 1, startY + y + 1, startZ + z,
                            startX + x + 1, startY + y + 1, startZ + z + 1,
                            startX + x, startY + y + 1, startZ + z + 1,
                        });

                        meshTexCoords.insert(meshTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

                        meshShadingValues.insert(meshShadingValues.end(), {        
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                            0.8f, 0.8f, 0.8f, 0.8f,
                        });
                    }
                    // Bottom Face
                    if (IsBlockHidden(x, y, z, 5, water))
                    {
                        meshVertexPositions.insert(meshVertexPositions.end(), {
                            startX + x, startY + y, startZ + z, // Vertex 0
                            startX + x, startY + y, startZ + z + 1, // Vertex 1
                            startX + x + 1, startY + y, startZ + z + 1, // Vertex 2
                            startX + x + 1, startY + y, startZ + z, // Vertex 3
                        });

                        meshTexCoords.insert(meshTexCoords.end(), topTexCoords.begin(), topTexCoords.end());

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
