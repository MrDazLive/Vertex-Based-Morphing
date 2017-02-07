#pragma once

#include <vector>

class GameObject;

class Component abstract {
public:
	virtual const unsigned int getIndex() const = 0;
protected:
	static unsigned int getNewIndex();
private:
	static unsigned int m_count;
};

unsigned int Component::m_count = 0;
unsigned int Component::getNewIndex() {
	return ++m_count;
}

template <typename T>
class BaseComponent abstract : public Component {
friend class GameObject;
public:
							~BaseComponent();

	const GameObject*		getGameObject	() const;
	const bool				isActive		() const;
	const void				setActive		(bool);

	const unsigned int		getIndex		() const override;

	virtual void			OnStart			() {}
	virtual void			OnAwake			() {}
	virtual void			OnUpdate		() {}
	virtual void			OnSleep			() {}
	virtual void			OnEnd			() {}

	virtual void			OnEnable		() {}
	virtual void			OnDisable		() {}

	static T**				getAll			();
protected:
							BaseComponent(T* const, GameObject* const);
private:
	bool						m_active;
	
	const	T*			const	m_self;
	const	GameObject*	const	m_gameObject;

	static	unsigned int		m_index;
	static	std::vector<T*>		m_instance;
};

template <typename T>
unsigned int BaseComponent<T>::m_index = Component::getNewIndex();

template <typename T>
std::vector<T*> BaseComponent<T>::m_instance;

template <typename T>
BaseComponent<T>::BaseComponent(T* const com, GameObject* const obj) : m_self(com), m_gameObject(obj) {
	m_instance.push_back(com);
}

template <typename T>
BaseComponent<T>::~BaseComponent() {
	m_instance.erase(std::remove(m_instance.begin(), m_instance.end(), m_self), m_instance.end());
	m_instance.shrink_to_fit();
}

template <typename T>
const GameObject* BaseComponent<T>::getGameObject() const {
	return m_gameObject;
}

template <typename T>
const bool BaseComponent<T>::isActive() const {
	return m_active;
}

template <typename T>
const void BaseComponent<T>::setActive(bool status) {
	m_active = status;
}

template <typename T>
const unsigned int BaseComponent<T>::getIndex() const {
	return m_index;
}

template <typename T>
T** BaseComponent<T>::getAll() {
	return m_instance.data();
}