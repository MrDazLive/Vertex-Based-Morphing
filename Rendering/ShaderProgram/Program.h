#pragma once

#include <string>
#include <GL\glew.h>
#include <Utilities\Helper\Global.h>
#include <Utilities\BaseClass\Handler.h>

class Shader;
class Texture;

class Program final : public Handler<Program> {
public:
                    Program                 (const std::string&);
                    ~Program                ();

    const GLuint    getProgram              () const;
    const GLuint    getInAttributeCount     () const;
    const GLuint    getOutAttributeCount    () const;
    const GLuint    getStatus               () const;

    void            setVertexSubroutine     (const std::string&);
    void            setFragmentSubroutine   (const std::string&);

    void            Link                    ();
    void            LogInfo                 ();
    void            SetActive               ();

    static void     Reset                   ();

    void            AddShader               (const Shader* const);
    void            AddInAttribute          (const std::string&);
    void            AddOutAttribute         (const std::string&);
    void            BindTexture             (const Texture* const, const std::string&);
    Template void   BindUniformBlock        (const std::string&);
    Variadic void   AddShader               (const Shader* const, const V...);
    Variadic void   AddInAttribute          (const std::string&, const V...);
    Variadic void   AddOutAttribute         (const std::string&, const V...);
private:
    GLuint          GenProgram              ();
    void            BindSubroutine          (const GLenum, const std::string&);

    const GLuint    m_program               { 0 };
    GLuint          m_inAttributeCount      { 0 };
    GLuint          m_outAttributeCount     { 0 };
    GLuint          m_textureCount          { 0 };
    GLuint          m_status                { GL_FALSE };
    std::string     m_vertexSubroutine      { "" };
    std::string     m_fragmemtSubroutine    { "" };
};

Template
void Program::BindUniformBlock(const std::string& name) {
    T::BindBlock(name, this);
}

Variadic
void Program::AddShader(const Shader* const ptr, const V... var) {
    AddShader(ptr);
    AddShader(var...);
}

Variadic
void Program::AddInAttribute(const std::string& name, const V... var) {
    AddInAttribute(name);
    AddInAttribute(var...);
}

Variadic
void Program::AddOutAttribute(const std::string& name, const V... var) {
    AddOutAttribute(name);
    AddOutAttribute(var...);
}