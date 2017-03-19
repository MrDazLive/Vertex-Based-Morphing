#pragma once

struct RayHit final {
public:
    bool            detected    { false };
    unsigned int    meshIndex   { 0 };
};