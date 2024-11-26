#pragma once

#include <glm/glm.hpp>

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;

    AABB(glm::vec3 minPoint, glm::vec3 maxPoint)
        : min(minPoint), max(maxPoint) {}
};