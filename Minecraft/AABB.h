#pragma once

#include <glm/glm.hpp>

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;

    bool Intersects(const AABB& other) const
    {
        return (min.x <= other.max.x && max.x >= other.min.x) &&
               (min.y <= other.max.y && max.y >= other.min.y) &&
               (min.z <= other.max.z && max.z >= other.min.z);
    }

    bool operator==(const AABB& other) const
    {
        return (min == other.min && max == other.max);
    }
};