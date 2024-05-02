#include "Raycast.h"

RaycastResult Raycast(const glm::vec3& origin, const glm::vec3& direction, float distance, Chunk& chunk)
{
    RaycastResult result;
    result.hit = false;

    glm::vec3 currentPos = glm::vec3(origin.x - chunk.position.x, origin.y, origin.z - chunk.position.y);
    for (float t = 0; t < distance; t += 0.1f)
    {
        currentPos = origin + direction + t;

        int index = currentPos.x + CHUNK_WIDTH * (currentPos.y + CHUNK_HEIGHT * currentPos.z);

        if (chunk.blocks[index] == 1)
        {
            result.hit = true;
            result.blockPos = currentPos;
            break;
        }
    }
    std::cout << result.hit << std::endl;
    return result;
}