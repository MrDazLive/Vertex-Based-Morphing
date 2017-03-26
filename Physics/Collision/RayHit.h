#pragma once

struct RayHit final {
public:
    bool                        detected        { false };
    unsigned int                meshIndex       { 0 };
    unsigned int                colliderIndex   { 0 };
    std::vector<unsigned int>   triangles;
};