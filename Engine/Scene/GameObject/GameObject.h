#pragma once

#include "../Utilities/Handler.h"

class Component;

class GameObject final : public Handler<GameObject> {
public:
					GameObject	(const std::string& name) : Handler<GameObject>(this, name) {}
					~GameObject	() = default;

	const bool		isActive	() const;
	const void		setActive	(bool);

	void			OnUpdate	() {}
private:
	bool			m_active	{ true };
	std::unordered_map<unsigned int, Component*> m_component;
};