#pragma once

#include "Vertex.h"
#include "Vector2.h"
#include "Vector3.h"
#include "..\BaseClass\Handler.h"

class Mesh final : public Handler<Mesh> {
public:
						Mesh				(const std::string&);
						~Mesh				();

	const unsigned int	getElementCount		() const;
	const unsigned int	getVertexCount		() const;

	const unsigned int*	getElementArray		() const;
	const Vertex*		getVertexArray		() const;
	const Vector3*		getPositionArray	() const;
	const Vector3*		getNormalArray		() const;
	const Vector2*		getUVArray			() const;

	void				LoadFromFile		(const std::string&);
private:
	std::vector<unsigned int> m_elementArray;
	std::vector<Vertex> m_vertexArray;
	std::vector<Vector3> m_positionsArray;
	std::vector<Vector3> m_normalArray;
	std::vector<Vector2> m_uvArray;
};