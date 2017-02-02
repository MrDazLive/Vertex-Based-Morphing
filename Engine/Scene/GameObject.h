#pragma once

#include "../Utilities/Handler.h"

class GameObject : public Handler<GameObject> {
public:
	GameObject(const std::string& name) : Handler<GameObject>(this, name) {}
	~GameObject() = default;
protected:
};