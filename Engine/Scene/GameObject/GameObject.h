#pragma once

#include <functional>
#include <Utilities\BaseClass\Handler.h>

#define Template template <typename T>

class Component;

class GameObject final : public Handler<GameObject> {
public:
						GameObject		(const std::string&);
						~GameObject		();

	const bool			isActive		() const;
	const void			setActive		(bool);

	void				OnStart			();
	void				OnAwake			();
	void				OnUpdate		();
	void				OnSleep			();
	void				OnEnd			();

	Template Component* const	AddComponent	();
	Template Component* const	GetComponent	();
	Template void		RemoveComponent	();
private:
	using Map = std::unordered_map<unsigned int, Component*>;

	void				ComponentMethod	(std::function<void(Component* const)>);

	bool				m_active	{ true };
	Map					m_component	{ };
};

Template Component* const GameObject::AddComponent() {
	Component* ptr = new T(this);
	m_component.emplace(ptr->getIndex(), ptr);
	return ptr;
}

Template Component* const GameObject::GetComponent() {
	T obj(this);
	Component* ptr = m_component[obj.getIndex()];
	return ptr;
}

Template void GameObject::RemoveComponent() {
	T obj(this);
	delete m_component[obj.getIndex()];
	m_component.erase(obj.getIndex());
}