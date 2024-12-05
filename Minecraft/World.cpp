#include "World.h"

World::World(int RenderDistance, int worldSize)
    : renderDistance(RenderDistance), WorldSize(worldSize)
{
    chunks.resize(WorldSize);
    for (int x = 0; x < WorldSize; x++)
    {
        chunks[x].resize(WorldSize);

        for (int y = 0; y < WorldSize; y++)
        {
            chunks[x][y] = nullptr;
        }
    }
}

World::~World()
{
    
}

void World::ManageChunks(glm::vec2 PlayerPosition)
{
    int px = static_cast<int>(PlayerPosition.x / CHUNK_WIDTH);
    int py = static_cast<int>(PlayerPosition.y / CHUNK_LENGTH);

    //std::cout << "(" << px << ", " << py << ")" << std::endl;
    for (int x = 0; x < WorldSize; x++)
    {
        for (int y = 0; y < WorldSize; y++)
        {
            int distance = glm::distance(glm::vec2(px, py), glm::vec2(x, y));
            if (distance > renderDistance)
            {
                UnloadChunk(x, y);
            }
            else
            {
                if (chunks[x][y] == nullptr)
                {
                    LoadChunk(x, y, x, y);
                }
            }
        }
    }
}

void World::UnloadChunk(int x, int y)
{
    if (chunks[x][y] != nullptr)
    {
        std::vector<AABB> chunkCollider = chunks[x][y]->GetColliders();
        for (const AABB& collider : chunkCollider)
        {
            worldCollision.erase(collider);  // Erase directly from unordered_set
        }
    }

    delete chunks[x][y];
    chunks[x][y] = nullptr;
}

#include <unordered_set>

void World::LoadChunk(int x, int y, int chunkX, int chunkY)
{
    Chunk* newChunk = new Chunk(glm::vec2(chunkX, chunkY), simplexNoise, 10);
    newChunk->GenerateCollision();

    std::vector<AABB> colliders = newChunk->GetColliders();

    for (const AABB& collider : colliders)
    {
        worldCollision.insert(collider);
    }

    chunks[x][y] = newChunk;
}

void World::DrawChunks()
{
    size_t totalMemory = 0;

    for (auto& column : chunks)
    {
        for (auto& chunk : column)
        {
            if (chunk != nullptr)
            {
                grassTex.Bind();

                chunk->DrawChunk();
                totalMemory += sizeof(*chunk);
            }
        }
    }
}

int World::GetSize()
{
    return WorldSize;
}

std::unordered_set<AABB> World::GetWorldCollider()
{
    return worldCollision;
}