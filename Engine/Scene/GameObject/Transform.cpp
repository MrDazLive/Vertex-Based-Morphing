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
	float cos[3]{ std::cos(m_rotation.x), std::cos(m_rotation.y), std::cos(m_rotation.z) };
	float sin[3]{ std::sin(m_rotation.x), std::sin(m_rotation.y), std::sin(m_rotation.z) };

	glm::mat4 m;
	m[0][0] = cos[1] * cos[2] * m_scale.x;
	m[0][1] = -sin[2];
	m[0][2] = sin[1];
	m[0][3] = m_position.x;

	m[1][0] = sin[2];
	m[1][1] = cos[0] * cos[2] * m_scale.y;
	m[1][2] = -sin[0];
	m[1][3] = m_position.y;

	m[2][0] = -sin[1];
	m[2][1] = sin[0];
	m[2][2] = cos[0] * cos[1] * m_scale.z;
	m[2][3] = m_position.z;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1;

	return m;
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