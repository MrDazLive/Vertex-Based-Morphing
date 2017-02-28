#pragma once

#include <GL\glew.h>

#define Template template <typename T>

class VertexArray {
public:
                    VertexArray             ();
                    ~VertexArray            ();

    const GLuint    getArray                () const;

    void            SetActive               ();

    void            EnableAttribute         (const GLuint);
    void            EnableAttributeRange    (GLuint, const GLuint);
    void            DisableAttribute        (const GLuint);
    void            DisableAttributeRange   (GLuint, const GLuint);

    static void     Reset                   ();

    Template void   AddAttribute            (GLint, const GLvoid* = 0);
    Template void   AddAttributeDivisor     (GLint, const GLvoid* = 0);
private:
    static GLuint   GenArray                ();

    const GLuint    m_array                 { 0 };
    GLuint          m_attributeCount        { 0 };
};

Template void VertexArray::AddAttribute(GLint size, const GLvoid *ptr) {
    glEnableVertexAttribArray(m_attributeCount);
    glVertexAttribPointer(m_attributeCount, size, GL_FLOAT, GL_FALSE, sizeof(T), ptr);
    m_attributeCount++;
}

Template void VertexArray::AddAttributeDivisor(GLint size, const GLvoid *ptr) {
    AddAttribute<T>(size, ptr);
    glVertexAttribDivisor(m_attributeCount - 1, 1);
}