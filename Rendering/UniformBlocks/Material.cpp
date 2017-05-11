#include "Material.h"

#include <glm\glm.hpp>

#include "..\Texture\Texture.h"
#include "..\ShaderProgram\Program.h"

unsigned int UniformBlock<Material>::m_blockSize = 8;

unsigned int UniformBlock<Material>::getBlockSize() {
    return m_blockSize;
}

Material::Material(const std::string& name) : UniformBlock<Material>(this, name) {

}

const unsigned int Material::getShader() const {
    return m_shader;
}

const unsigned int Material::getDiffuse() const {
    return m_diffuse;
}

const unsigned int Material::getMorphDiffuse() const {
    return m_morphDiffuse;
}

const glm::vec3 Material::getColour() const {
    return m_colour;
}

const float Material::getMorph() const {
    return m_morph;
}

void Material::setShader(const std::string& name) {
    m_shader = Program::getWithName(name)->getIndex();
}

void Material::setDiffuse(const std::string& name) {
    m_diffuse = Texture::getWithName(name)->getIndex();
}

void Material::setMorphDiffuse(const std::string& name) {
    m_morphDiffuse = Texture::getWithName(name)->getIndex();
}

void Material::setColour(const glm::vec3& colour) {
    m_colour = colour;
}

void Material::setMorph(const float& morph) {
    m_morph = glm::clamp(morph, 0.0f, 1.0f);
}

void Material::slideMorph(const float& morph) {
    setMorph(m_morph + morph);
}

void Material::BuildBlock(float* const ptr) {
    ptr[0] = m_colour.x;
    ptr[1] = m_colour.y;
    ptr[2] = m_colour.z;
    ptr[3] = m_diffuse;

    ptr[4] = m_morph;
    ptr[5] = m_morphDiffuse;
    ptr[6] = 0;
    ptr[7] = 0;
}