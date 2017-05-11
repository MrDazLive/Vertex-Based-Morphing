#pragma once

#include <glm\glm.hpp>

struct RayHit final {
public:
    bool                        detected        { false };
    unsigned int                meshIndex       { 0 };
    unsigned int                colliderIndex   { 0 };
    unsigned int                triangle        { 0 };
    glm::vec3                   point           { 0.0f, 0.0f, 0.0f };
};