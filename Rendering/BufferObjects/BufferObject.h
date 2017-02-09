#pragma once

#include <GL\glew.h>
#include <vector>

#define Template template <typename T>

class BufferObject abstract {
public:
					BufferObject	(GLenum, GLenum);
					~BufferObject	();

	const GLuint	getBuffer		() const;
	const GLenum	getTarget		() const;
	const GLenum	getUsage		() const;

	void			SetActive		();
	void			BindRange		(GLuint, GLintptr, GLuint);

	Template void	BufferData		(T* const, GLsizeiptr);
protected:

private:
	static GLuint	GenBuffer		();

	const GLuint	m_buffer;
	const GLenum	m_target;
	const GLenum	m_usage;
};

Template void BufferObject::BufferData(T* const data, GLsizeiptr size) {
	SetActive();
	glBufferData(m_target, size, data, m_usage);
}