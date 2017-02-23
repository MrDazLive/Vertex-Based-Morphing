#include "BufferObject.h"

BufferObject::BufferObject(GLenum target, GLenum usage) : m_target(target), m_usage(usage), m_buffer(GenBuffer()) {

}

BufferObject::~BufferObject() {
	glDeleteBuffers(1, &m_buffer);
}

const GLuint BufferObject::getBuffer() const {
	return m_buffer;
}

const GLenum BufferObject::getTarget() const {
	return m_target;
}

const GLenum BufferObject::getUsage() const {
	return m_usage;
}

void BufferObject::SetActive() {
	glBindBuffer(m_target, m_buffer);
}

void BufferObject::BindRange(GLuint index, GLintptr offset, GLuint size) {
	SetActive();
	glBindBufferRange(m_target, index, m_buffer, offset, size);
}

GLuint BufferObject::GenBuffer() {
	GLuint index{ 0 };
	glGenBuffers(1, &index);
	return index;
}