#pragma once

#include <glm\glm.hpp>

struct Vertex final {
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};