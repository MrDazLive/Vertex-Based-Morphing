#pragma once

#include "BufferObject.h"

class UniformBuffer final : public BufferObject {
public:
	UniformBuffer(GLenum);
	~UniformBuffer();

	static void Reset();
private:
};