#include "Camera.h"

glm::vec3 Camera::m_position = glm::vec3(0.0f, 0.0f, -10.0f);
glm::vec3 Camera::m_direction = glm::vec3(0.0f, 0.0f, 1.0f);

const void Camera::Rotate(const glm::vec3& offset) {
	m_direction += offset;
	m_direction = glm::normalize(m_direction);
}

const void Camera::Translate(const glm::vec3& offset) {
	m_position += offset;
}

const glm::mat4 Camera::ViewMatrix() {
	return glm::lookAt(m_position, m_direction, glm::vec3(0, 1, 0));
}