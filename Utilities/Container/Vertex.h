#pragma once

#include "Vector2.h"
#include "Vector3.h"

struct Vertex final {
public:
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};