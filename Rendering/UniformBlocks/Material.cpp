#include "Material.h"

#include <glm\glm.hpp>

#include "..\ShaderProgram\Program.h"

unsigned int UniformBlock<Material>::m_blockSize = 4;

unsigned int UniformBlock<Material>::getBlockSize() {
    return m_blockSize;
}

Material::Material(const std::string& name) : UniformBlock<Material>(this, name) {

}

const unsigned int Material::getShader() const {
    return m_shader;
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
    ptr[3] = m_morph;
}