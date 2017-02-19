#pragma once

#include "..\VertexObjects\VertexArray.h"
#include "..\BufferObjects\ArrayBuffer.h"
#include "..\BufferObjects\ElementBuffer.h"

#include <map>
#include <glm\glm.hpp>
#include <unordered_map>

class Geometry final {
public:
					Geometry			() = default;
					~Geometry			() = default;

	void			FillBuffers			();
	void			BuildArray			();

	void			Draw				();
	void			DrawRequest			(const unsigned int, const unsigned int, const glm::mat4&);
private:
	struct Command;
	struct Instance {
		glm::mat4 model;
		unsigned int material;
	};
	struct MeshOffsets {
		unsigned int elementOffset;
		unsigned int vertexOffset;
	};

	ArrayBuffer		m_vertexBuffer		{ GL_STATIC_DRAW };
	ArrayBuffer		m_instanceBuffer	{ GL_DYNAMIC_DRAW };
	BufferObject	m_indirectBuffer	{ GL_DRAW_INDIRECT_BUFFER, GL_DYNAMIC_DRAW };
	ElementBuffer	m_elementBuffer		{};
	VertexArray		m_vertexArray		{};

	std::unordered_map<unsigned int, MeshOffsets>										m_meshOffsets;
	std::unordered_map<unsigned int, std::map<unsigned int, std::vector<Instance>>>		m_commandList;
};