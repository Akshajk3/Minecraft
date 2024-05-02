#pragma once

#include <glm/glm.hpp>
#include "Chunk.h"

struct RaycastResult
{
    bool hit;
    glm::ivec3 blockPos;
};


RaycastResult Raycast(const glm::vec3& origin, const glm::vec3& direction, float distance, Chunk& chunk);