#pragma once

#include <vector>
#include <unordered_set>

#include "Chunk.h"
#include "SimplexNoise.h"
#include "Texture.h"
#include "AABB.h"

class World
{
public:
	World(int RenderDistance, int worldSize);
	~World();

	void DrawChunks();
	void DeleteChunks();
	void ManageChunks(glm::vec2 PlayerPosition);
	void UnloadChunk(int x, int y);
	void LoadChunk(int x, int y, int px, int py);
	std::unordered_set<AABB> GetWorldCollider();

	int GetSize();

private:
	std::vector<std::vector<Chunk*>> chunks;
	int renderDistance;
	int WorldSize;

	SimplexNoise simplexNoise;

	std::unordered_set<AABB> worldCollision;

	Texture dirtTex = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture stoneTex = Texture("textures/cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture grassTex = Texture("textures/texture_atlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
};
