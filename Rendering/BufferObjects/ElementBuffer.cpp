#include "ElementBuffer.h"

ElementBuffer::ElementBuffer() : BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {

}

ElementBuffer::~ElementBuffer() {

}

void ElementBuffer::Reset() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}