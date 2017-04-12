#pragma once

#include <GL\glew.h>
#include <Utilities\BaseClass\Handler.h>

class Image;

class Texture : public Handler<Texture> {
public:
                    Texture         (const std::string&, GLenum, GLenum = GL_COLOR_ATTACHMENT0);
                    ~Texture        ();

    const GLuint    getBuffer       () const;
    const GLenum    getTarget       () const;
    const GLenum    getAttachment   () const;

    void            SetActive       ();
    void            BufferImage     (Image* const);

    static void     Reset           (GLenum);
private:
    static GLuint   GenBuffer       ();

    const GLuint    m_buffer        { 0 };
    const GLenum    m_target        { 0 };
    const GLenum    m_attachment    { 0 };
};