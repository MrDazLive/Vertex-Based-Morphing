#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(GLenum usage) : BufferObject(GL_UNIFORM_BUFFER, usage) {

}

UniformBuffer::~UniformBuffer() {
	
}