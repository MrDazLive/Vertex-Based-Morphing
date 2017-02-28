#include "Transform.h"

#include <math.h>

Transform::Transform(GameObject* const ptr) : BaseComponent<Transform>(this, ptr) {

}

Transform::~Transform() {

}

const glm::vec3& Transform::getPosition() const {
	return m_position;
}

const glm::vec3& Transform::getRotation() const {
	return m_rotation;
}

const glm::vec3& Transform::getScale() const {
	return m_scale;
}

const glm::mat4	 Transform::getTransformMatrix() const {
	float cos[3]{ std::cosf(m_rotation.x), std::cosf(m_rotation.y), std::cosf(m_rotation.z) };
	float sin[3]{ std::sinf(m_rotation.x), std::sinf(m_rotation.y), std::sinf(m_rotation.z) };

	glm::mat4 translate;
	translate[3][0] = m_position.x;
	translate[3][1] = m_position.y;
	translate[3][2] = m_position.z;

	glm::mat4 rotateX;
	rotateX[1][1] = cos[0];
	rotateX[1][2] = -sin[0];
	rotateX[2][1] = sin[0];
	rotateX[2][2] = cos[0];

	glm::mat4 rotateY;
	rotateY[0][0] = cos[1];
	rotateY[0][2] = -sin[1];
	rotateY[2][0] = sin[1];
	rotateY[2][2] = cos[1];

	glm::mat4 rotateZ;
	rotateZ[0][0] = cos[2];
	rotateZ[0][1] = -sin[2];
	rotateZ[1][0] = sin[2];
	rotateZ[1][1] = cos[2];

	glm::mat4 scale;
	scale[0][0] = m_scale.x;
	scale[1][1] = m_scale.y;
	scale[2][2] = m_scale.z;

	return translate * rotateX * rotateY * rotateZ * scale;
}

void Transform::setPosition(const glm::vec3& position) {
	m_position = position;
}

void Transform::setRotation(const glm::vec3& rotation) {
	m_rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale) {
	m_scale = scale;
}

void Transform::Translate(const glm::vec3& offset) {
	m_position.x += offset.x;
	m_position.y += offset.y;
	m_position.z += offset.z;
}

void Transform::Rotate(const glm::vec3& offset) {
	m_rotation.x += offset.x;
	m_rotation.y += offset.y;
	m_rotation.z += offset.z;
}