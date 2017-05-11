#include "Texture.h"

#include "Image.h"

Texture::Texture(const std::string& name, GLenum target, GLenum attachment) :
    Handler<Texture>(this, name), m_buffer(GenBuffer()), m_target(target), m_attachment(attachment) { }

Texture::~Texture() {
    glDeleteTextures(1, &m_buffer);
}

const GLuint Texture::getBuffer() const {
    return m_buffer;
}

const GLenum Texture::getTarget() const {
    return m_target;
}

const GLenum Texture::getAttachment() const {
    return m_attachment;
}

void Texture::SetActive() const {
    glBindTexture(m_target, m_buffer);
}

void Texture::BufferImage(Image* const image) {
    SetActive();

    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(m_target, 0, GL_RGBA,
        image->getWidth(), image->getHeight(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, image->getData());

    glGenerateMipmap(m_target);
    glBindTexture(m_target, 0);

    Texture::Reset(m_target);
}

void Texture::Reset(GLenum target) {
    glBindTexture(target, 0);
}

GLuint Texture::GenBuffer() {
    GLuint index{ 0 };
    glGenTextures(1, &index);
    return index;
}