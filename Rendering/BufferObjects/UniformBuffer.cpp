#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(GLenum usage) : BufferObject(GL_UNIFORM_BUFFER, usage) {

}

UniformBuffer::~UniformBuffer() {
	
}

void UniformBuffer::Reset() {
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}