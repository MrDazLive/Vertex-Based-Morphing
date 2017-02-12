#include "Mesh.h"

#include "..\Helper\File.h"

Mesh::Mesh(const std::string& name) : Handler<Mesh>(this, name) {

}

Mesh::~Mesh() {

}

const unsigned int Mesh::getElementCount() const {
	return (unsigned int)m_elementArray.capacity();
}

const unsigned int Mesh::getVertexCount() const {
	return (unsigned int)m_vertexArray.capacity();
}

const unsigned int*	Mesh::getElementArray() const {
	return m_elementArray.data();
}

const Vertex* Mesh::getVertexArray() const {
	return m_vertexArray.data();
}

const Vector3* Mesh::getPositionArray() const {
	return m_positionsArray.data();
}

const Vector3* Mesh::getNormalArray() const {
	return m_normalArray.data();
}

const Vector2* Mesh::getUVArray() const {
	return m_uvArray.data();
}

void Mesh::LoadFromFile(const std::string& name) {
	File::toMesh(name, m_vertexArray, m_elementArray);
	for (Vertex vertex : m_vertexArray) {
		m_positionsArray.push_back(vertex.position);
		m_normalArray.push_back(vertex.normal);
		m_uvArray.push_back(vertex.uv);
	}
}