#include "Camera.h"

#include "..\UniformBlocks\Perspective.h"

glm::vec2 Camera::m_resolution  = glm::vec2(1080.0f, 720.0f);
glm::vec3 Camera::m_position    = glm::vec3(0.0f, 0.0f, -10.0f);
glm::vec3 Camera::m_target      = glm::vec3(0.0f, 0.0f, 0.0f);

const void Camera::Target(const glm::vec3& target) {
    m_target = target;
}

const void Camera::Translate(const glm::vec3& offset) {
    m_position += offset;
}

const glm::vec2& Camera::Resolution() {
    return m_resolution;
}

const glm::vec3& Camera::Position() {
    return m_position;
}

const glm::vec3 Camera::Direction() {
    return glm::normalize(m_target - m_position);
}

const glm::vec3 Camera::DirectionFromPoint(const glm::vec2& cursor) {
    const glm::vec2 point{ cursor.x, m_resolution.y - cursor.y };
    return glm::normalize(
        glm::unProject(
            glm::vec3(point, 1.0f),
            ViewMatrix(),
            Perspective::getWithIndex(0)->getProjection(),
            glm::vec4(0.0f, 0.0f, m_resolution)
        )
    );
}

const glm::mat4 Camera::ViewMatrix() {
    return glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
}