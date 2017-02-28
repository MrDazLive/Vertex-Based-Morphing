#include "Program.h"

#include <iostream>

#include "Shader.h"

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
}

void Program::SetSubroutine(GLenum type, const std::string& name) {
    GLuint index = glGetSubroutineIndex(m_program, type, name.c_str());
    glUniformSubroutinesuiv(type, 1, &index);
}

void Program::Reset() {
    glUseProgram(0);
}

void Program::AddShader(const Shader* shader) {
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

GLuint Program::GenProgram() {
    return glCreateProgram();
}