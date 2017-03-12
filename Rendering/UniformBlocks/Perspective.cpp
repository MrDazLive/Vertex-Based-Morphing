#include "Perspective.h"

unsigned int UniformBlock<Perspective>::m_blockSize = 32;

unsigned int UniformBlock<Perspective>::getBlockSize() {
    return m_blockSize;
}

Perspective::Perspective(const std::string& name) : UniformBlock<Perspective>(this, name) {

}

const glm::mat4& Perspective::getProjection() const {
    return m_projection;
}

const glm::mat4& Perspective::getView() const {
    return m_view;
}

void Perspective::setProjection(const glm::mat4& projection) {
    m_projection = projection;
}

void Perspective::setView(const glm::mat4& view) {
    m_view = view;
}

void Perspective::BuildBlock(float* const ptr) {
    for (unsigned int i = 0; i < 16; i++) {
        ptr[i] = m_projection[i / 4][i % 4];
        ptr[i + 16] = m_view[i / 4][i % 4];
    }
}