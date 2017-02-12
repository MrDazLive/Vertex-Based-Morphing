#include "GameObject.h"

GameObject::GameObject(const std::string& name) : Handler<GameObject>(this, name) {
	transform = (Transform*)AddComponent<Transform>();
}

GameObject::~GameObject() {
	ComponentMethod([](Component* const ptr) { delete ptr; });
}

const bool GameObject::isActive() const {
	return m_active;
}

const void GameObject::setActive(bool status) {
	if (m_active != status) {
		m_active = status;
		m_active ?
			ComponentMethod([](Component* const ptr) { ptr->OnEnable(); }) :
			ComponentMethod([](Component* const ptr) { ptr->OnDisable(); });
	}
}

void GameObject::OnStart() {
	ComponentMethod([](Component* const ptr) { ptr->OnStart(); });
}

void GameObject::OnAwake() {
	ComponentMethod([](Component* const ptr) { ptr->OnAwake(); });
}

void GameObject::OnUpdate() {
	ComponentMethod([](Component* const ptr) { ptr->OnUpdate(); });
}

void GameObject::OnSleep() {
	ComponentMethod([](Component* const ptr) { ptr->OnSleep(); });
}

void GameObject::OnEnd() {
	ComponentMethod([](Component* const ptr) { ptr->OnEnd(); });
}

void GameObject::ComponentMethod(std::function<void(Component* const)> method) {
	for (auto& it : m_component) {
		if (it.second->isActive()) {
			method(it.second);
		}
	}
}