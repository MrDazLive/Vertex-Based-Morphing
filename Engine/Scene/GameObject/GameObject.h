#pragma once

#include "../Utilities/Handler.h"

class Component;

class GameObject final : public Handler<GameObject> {
public:
	GameObject(const std::string& name) : Handler<GameObject>(this, name) {}
	~GameObject() = default;

	void OnUpdate() {}
private:
	std::unordered_map<unsigned int, Component*> m_component;
};