#pragma once

#include <string>
#include <GL\glew.h>

class Shader final {
public:
					Shader			(GLenum);
					~Shader			();

	const GLuint	getShader		() const;
	const GLuint	getStatus		() const;
	const GLenum	getType			() const;

	void			LogInfo			();
	void			LoadFromFile	(const std::string&);
private:
	static GLuint	GenShader		(GLenum);

	const GLuint	m_shader		{};
	const GLenum	m_type			{};
	GLuint			m_status		{};
};