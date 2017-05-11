#include "Program.h"

#include <iostream>

#include "Shader.h"
#include "..\Texture\Texture.h"

Program::Program(const std::string& name) : Handler<Program>(this, name), m_program(GenProgram()) {

}

Program::~Program() {
    glDeleteProgram(m_program);
}

const GLuint Program::getProgram() const {
    return m_program;
}

const GLuint Program::getInAttributeCount() const {
    return m_inAttributeCount;
}

const GLuint Program::getOutAttributeCount() const {
    return m_outAttributeCount;
}

const GLuint Program::getStatus() const {
    return m_status;
}

void Program::Link() {
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, (GLint *)&m_status);
    if (m_status != GL_TRUE) {
        LogInfo();
    }
}

void Program::LogInfo() {
    const int string_length = 1024;
    GLchar log[string_length] = "";
    glGetProgramInfoLog(m_program, string_length, NULL, log);
    std::cerr << log << std::endl;
}

void Program::SetActive() {
    glUseProgram(m_program);
    BindSubroutine(GL_VERTEX_SHADER, m_vertexSubroutine);
    BindSubroutine(GL_FRAGMENT_SHADER, m_fragmemtSubroutine);
}

void Program::setVertexSubroutine(const std::string& name) {
    m_vertexSubroutine = name;
}

void Program::setFragmentSubroutine(const std::string& name) {
    m_fragmemtSubroutine = name;
}

void Program::Reset() {
    glUseProgram(0);
}

void Program::AddShader(const Shader* const shader) {
    glAttachShader(m_program, shader->getShader());
}

void Program::AddInAttribute(const std::string& name) {
    glBindAttribLocation(m_program, m_inAttributeCount, name.c_str());
    m_inAttributeCount++;
}

void Program::AddOutAttribute(const std::string& name) {
    glBindAttribLocation(m_program, m_outAttributeCount, name.c_str());
    m_outAttributeCount++;
}

void Program::BindTexture(const Texture* const texture, const std::string& name) {
    glActiveTexture(GL_TEXTURE0 + m_textureCount);
    texture->SetActive();
    GLuint index = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(index, m_textureCount++);
}

GLuint Program::GenProgram() {
    return glCreateProgram();
}

void Program::BindSubroutine(const GLenum target, const std::string& name) {
    GLuint index = glGetSubroutineIndex(m_program, target, name.c_str());
    glUniformSubroutinesuiv(target, 1, &index);
}