#pragma once

#include "..\VertexObjects\VertexArray.h"
#include "..\BufferObjects\ArrayBuffer.h"
#include "..\BufferObjects\ElementBuffer.h"

#include <unordered_map>

class Geometry final {
public:
					Geometry			() = default;
					~Geometry			() = default;

	void			FillBuffers			();
	void			BuildArray			();

	void			ActivateArray		();
private:
	ArrayBuffer		m_vertexBuffer		{ GL_STATIC_DRAW };
	ArrayBuffer		m_instanceBuffer	{ GL_DYNAMIC_DRAW };
	ElementBuffer	m_elementBuffer		{};

	VertexArray		m_vertexArray		{};

	struct MeshIndices {
		unsigned int elementCount;
		unsigned int vertexCount;

		unsigned int elementOffset;
		unsigned int vertexOffset;
	};

	std::unordered_map<unsigned int, MeshIndices> m_meshIndices;
};