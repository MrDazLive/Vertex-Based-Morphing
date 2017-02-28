#include "Camera.h"

glm::vec3 Camera::m_position = glm::vec3(0.0f, 0.0f, -10.0f);
glm::vec3 Camera::m_target = glm::vec3(0.0f, 0.0f, 0.0f);

const void Camera::Target(const glm::vec3& target) {
    m_target = target;
}

const void Camera::Translate(const glm::vec3& offset) {
    m_position += offset;
}

const glm::vec3& Camera::Position() {
    return m_position;
}

const glm::vec3& Camera::Direction() {
    return glm::normalize(m_target - m_position);
}

const glm::mat4 Camera::ViewMatrix() {
    return glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
}