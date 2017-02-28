#include "VertexArray.h"

#include <assert.h>

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

void VertexArray::EnableAttribute(const GLuint index) {
    assert(index < m_attributeCount);
    glEnableVertexAttribArray(index);
}

void VertexArray::EnableAttributeRange(GLuint index, const GLuint end) {
    assert(end <= m_attributeCount);
    do {
        glEnableVertexAttribArray(index);
    } while (++index < end);
}

void VertexArray::DisableAttribute(const GLuint index) {
    assert(index < m_attributeCount);
    glDisableVertexAttribArray(index);
}

void VertexArray::DisableAttributeRange(GLuint index, const GLuint end) {
    assert(end <= m_attributeCount);
    do {
        glDisableVertexAttribArray(index);
    } while (++index < end);
}


void VertexArray::Reset() {
    glBindVertexArray(0);
}

GLuint VertexArray::GenArray() {
    GLuint index{ 0 };
    glGenVertexArrays(1, &index);
    return index;
}