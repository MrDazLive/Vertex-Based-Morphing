#include "Shader.h"

#include <iostream>
#include <Utilities\Helper\File.h>

Shader::Shader(GLenum type) : m_type(type), m_shader(GenShader(type)) {

}

Shader::~Shader() {
    glDeleteShader(m_shader);
}

const GLuint Shader::getShader() const {
    return m_shader;
}

const GLuint Shader::getStatus() const {
    return m_status;
}

const GLenum Shader::getType() const {
    return m_type;
}

void Shader::LogInfo() {
    const int string_length = 1024;
    GLchar log[string_length] = "";
    glGetShaderInfoLog(m_shader, string_length, NULL, log);
    std::cerr << log << std::endl;
}

void Shader::LoadFromFile(const std::string& name) {
    std::string shader_string = File::toString(name);
    const char *shader_code = shader_string.c_str();
    glShaderSource(m_shader, 1,
        (const GLchar **)&shader_code, NULL);
    glCompileShader(m_shader);
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, (GLint *)&m_status);
    if (m_status != GL_TRUE) {
        LogInfo();
    }
}

GLuint Shader::GenShader(GLenum type) {
    return glCreateShader(type);
}