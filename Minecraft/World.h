#pragma once

#include <vector>

#include "Chunk.h"
#include "SimplexNoise.h"
#include "Texture.h"
#include "Raycast.h"

class World
{
public:
	World(int RenderDistance, int worldSize);
	~World();

	void DrawChunks();
	void DeleteChunks();
	void ManageChunks(glm::vec2 PlayerPosition);
	void CheckChunkCollision(glm::vec3 position, glm::vec3 dir);
	void UnloadChunk(int x, int y);
	void LoadChunk(int x, int y, int px, int py);

	bool IsChunkLoaded(int x, int y);

	int GetSize();

private:
	std::vector<std::vector<Chunk*>> chunks;
	int renderDistance;
	int WorldSize;

	SimplexNoise simplexNoise;

	Texture dirtTex = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture stoneTex = Texture("textures/cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture grassTex = Texture("textures/texture_atlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
};
