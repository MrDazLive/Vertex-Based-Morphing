#include "VertexArray.h"

VertexArray::VertexArray() : m_array(GenArray()) {

}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_array);
}

const GLuint VertexArray::getArray() const {
	return m_array;
}

void VertexArray::SetActive() {
	glBindVertexArray(m_array);
}

void VertexArray::Reset() {
	glBindVertexArray(0);
}

GLuint VertexArray::GenArray() {
	GLuint index{ 0 };
	glGenVertexArrays(1, &index);
	return index;
}