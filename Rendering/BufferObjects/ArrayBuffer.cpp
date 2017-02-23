#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(GLenum usage) : BufferObject(GL_ARRAY_BUFFER, usage) {

}

ArrayBuffer::~ArrayBuffer() {

}

void ArrayBuffer::Reset() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}