#pragma once

#include <Utilities\Handler.h>
#include <GL\glew.h>

#include "..\BufferObjects\UniformBuffer.h"

#define Template template <typename T>

Template class UniformBlock abstract : public Handler<T> {
public:
						~UniformBlock	();

	static void			BufferBlock		();
protected:
						UniformBlock	(T* const, const std::string&);

	static unsigned int	getBlockSize	();
	virtual void		BuildBlock		(float*) = 0;
private:
	static UniformBuffer*	m_buffer;
	static unsigned int		m_blockSize;
};

Template
UniformBuffer* UniformBlock<T>::m_buffer = nullptr;

Template
unsigned int UniformBlock<T>::m_blockSize = 0;

Template
UniformBlock<T>::UniformBlock(T* const object, const std::string& name) : Handler<T>(object, name) {
	if (!m_buffer) {
		m_buffer = new UniformBuffer(GL_DYNAMIC_DRAW);
	}
}

Template
UniformBlock<T>::~UniformBlock() {
	delete m_buffer;
}

Template
unsigned int UniformBlock<T>::getBlockSize() {
	return m_blockSize;
}

Template
void UniformBlock<T>::BufferBlock() {
	unsigned int count = getCount();
	unsigned int block = getBlockSize();

	T** ptr = getAll();
	std::vector<float> vec;

	for (unsigned int i = 0; i < count; i++) {
		float arr[64];
		ptr[i]->BuildBlock(arr);
		for (unsigned int j = 0; j < block; j++) {
			vec.push_back(arr[j]);
		}
	}

	m_buffer->BufferData<float>(vec.data(), block);
}