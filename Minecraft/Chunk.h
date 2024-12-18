#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include <functional>
#include <chrono>

#include "Numbers.h"
#include "SimplexNoise.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Tree.h"
#include "AABB.h"

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 256
#define CHUNK_LENGTH 8
#define CHUNK_AREA CHUNK_WIDTH * CHUNK_LENGTH
#define CHUNK_VOL CHUNK_AREA * CHUNK_HEIGHT

class Chunk
{
public:
    Chunk(glm::vec2 pos, SimplexNoise& noise, int waterLevel);
    ~Chunk();

    void DeleteChunk();
    void DrawChunk();
    void GenerateCollision();
    
    bool IsBlockHidden(int x, int y, int z, int face, bool water) const;

    std::vector<AABB> GetColliders();
    
    glm::vec2 position;
    
    int blocks[CHUNK_VOL];

private:
    std::vector<GLfloat> meshVertexPositions;
    std::vector<GLfloat> meshTexCoords;
    std::vector<GLfloat> meshShadingValues;
    std::vector<GLuint> meshIndices;
    
    std::vector<std::thread> threads;
    std::atomic<bool> generationComplete;
    std::mutex generationMutex;

    std::mutex treeMutex;
    std::vector<Tree> trees;

    SimplexNoise noise;
    
    VAO vao;

    std::vector<AABB> colliders;

    void GenerateMesh();
    void GenerateChunkSection(Chunk& chunk, int startY, int endY, SimplexNoise& noise, int waterLevel);
};
