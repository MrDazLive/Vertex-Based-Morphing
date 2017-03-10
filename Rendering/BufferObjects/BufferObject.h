#pragma once

#include <GL\glew.h>
#include <Utilities\Helper\Global.h>

class BufferObject {
public:
                    BufferObject    (GLenum, GLenum);
                    ~BufferObject   ();

    const GLuint    getBuffer       () const;
    const GLenum    getTarget       () const;
    const GLenum    getUsage        () const;

    void            SetActive       ();
    void            BindRange       (GLuint, GLintptr = 0, GLuint = 0);

    Template void   BufferData      (T* const, GLsizeiptr);
protected:

private:
    static GLuint   GenBuffer       ();

    const GLuint    m_buffer        { 0 };
    const GLenum    m_target        { 0 };
    const GLenum    m_usage         { 0 };
};

Template void BufferObject::BufferData(T* const data, GLsizeiptr size) {
    SetActive();
    glBufferData(m_target, size, data, m_usage);
}