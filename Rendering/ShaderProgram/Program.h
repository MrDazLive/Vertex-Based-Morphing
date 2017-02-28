#pragma once

#include <string>
#include <GL\glew.h>
#include <Utilities\BaseClass\Handler.h>

#define Variadic template <typename ... V>

class Shader;

class Program final : public Handler<Program> {
public:
                    Program                 (const std::string&);
                    ~Program                ();

    const GLuint    getProgram              () const;
    const GLuint    getInAttributeCount     () const;
    const GLuint    getOutAttributeCount    () const;
    const GLuint    getStatus               () const;

    void            Link                    ();
    void            LogInfo                 ();
    void            SetActive               ();
    void            SetSubroutine           (GLenum, const std::string&);

    static void     Reset                   ();

    void            AddShader               (const Shader*);
    void            AddInAttribute          (const std::string&);
    void            AddOutAttribute         (const std::string&);
    Variadic void   AddShader               (const Shader*, const V...);
    Variadic void   AddInAttribute          (const std::string&, const V...);
    Variadic void   AddOutAttribute         (const std::string&, const V...);
private:
    GLuint          GenProgram              ();

    const GLuint    m_program               { 0 };
    GLuint          m_inAttributeCount      { 0 };
    GLuint          m_outAttributeCount     { 0 };
    GLuint          m_status                { GL_FALSE };
};

Variadic
void Program::AddShader(const Shader* ptr, const V... var) {
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