#include "Geometry.h"

#include <Utilities\Container\Mesh.h>

void Geometry::FillBuffers() {
	std::vector<unsigned int> elements;
	std::vector<Vertex> vertices;

	Mesh** ptrs = Mesh::getAll();
	const unsigned int meshCount = Mesh::getCount();
	for (unsigned int i = 0; i < meshCount; i++) {
		Mesh* ptr = ptrs[i];
		MeshIndices data;

		data.elementOffset = (unsigned int)elements.size();
		data.elementCount = ptr->getElementCount();
		elements.insert(elements.end(), ptr->getElementArray(), ptr->getElementArray() + data.elementCount);

		data.vertexOffset = (unsigned int)vertices.size();
		data.vertexCount = ptr->getVertexCount();
		vertices.insert(vertices.end(), ptr->getVertexArray(), ptr->getVertexArray() + data.vertexCount);

		m_meshIndices.emplace(ptr->getIndex(), data);
	}

	m_vertexBuffer.BufferData(vertices.data(), sizeof(Vertex) * vertices.size());
	m_elementBuffer.BufferData(elements.data(), sizeof(unsigned int) * elements.size());

	ArrayBuffer::Reset();
	ElementBuffer::Reset();
}

void Geometry::BuildArray() {
	m_vertexArray.SetActive();
	m_elementBuffer.SetActive();
	m_vertexBuffer.SetActive();
	m_vertexArray.AddAttribute<Vertex>(3);
	m_vertexArray.AddAttribute<Vertex>(3, (int*)(sizeof(glm::vec3)));
	m_vertexArray.AddAttribute<Vertex>(2, (int*)(sizeof(glm::vec3) * 2));
	/*m_instanceBuffer.SetActive();
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4);
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4)));
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4) * 2));
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4) * 3));*/

	ArrayBuffer::Reset();
	ElementBuffer::Reset();
	VertexArray::Reset();
}

void Geometry::ActivateArray() {
	m_vertexArray.SetActive();
}