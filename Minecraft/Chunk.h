#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

#include "Block.h"
#include "Numbers.h"
#include "SimplexNoise.h"

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 256
#define CHUNK_LENGTH 8
#define CHUNK_AREA CHUNK_WIDTH * CHUNK_LENGTH
#define CHUNK_VOL CHUNK_AREA * CHUNK_HEIGHT

class Chunk
{
public:
    Chunk(glm::vec2 pos, SimplexNoise& noise);
    ~Chunk();

    void DeleteChunk();
    void DrawChunk();
    
    bool IsBlockHidden(int x, int y, int z, int face) const;
    
    glm::vec2 position;
    
private:
    int blocks[CHUNK_VOL];

    std::vector<GLfloat> meshVertexPositions;
    std::vector<GLfloat> meshTexCoords;
    std::vector<GLfloat> meshShadingValues;
    std::vector<GLuint> meshIndices;
    

    Texture dirtTex = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture stoneTex = Texture("textures/cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture grassTex = Texture("textures/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    VAO vao;

    void GenerateMesh();
    void AddFace();
};
