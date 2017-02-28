#include "Component.h"

unsigned int Component::m_count = 0;

Component::Component(GameObject* const obj) : m_gameObject(obj) {
}

Component::~Component() {
}

const GameObject* Component::getGameObject() const {
    return m_gameObject;
}

const bool Component::isActive() const {
    return m_active;
}

const void Component::setActive(bool status) {
    if (m_active != status) {
        m_active = status;
        m_active ?
            this->OnEnable():
            this->OnDisable();
    }
}

unsigned int Component::getNewIndex() {
    return ++m_count;
}
