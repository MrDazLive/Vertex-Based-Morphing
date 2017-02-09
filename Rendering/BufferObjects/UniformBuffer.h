#pragma once

#include "BufferObject.h"

class UniformBuffer : public BufferObject {
public:
	UniformBuffer(GLenum);
	~UniformBuffer();
private:
};