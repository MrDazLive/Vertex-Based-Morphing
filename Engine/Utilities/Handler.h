#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

template<typename T>
class Handler abstract {
public:
							~Handler		();

	const unsigned int		getIndex		() const;
	const std::string&		getName			() const;

	static T*				getWithIndex	(const unsigned int);

	static T*				getWithName		(const std::string&);
	static T**				getAllWithName	(const std::string&);
protected:
							Handler			(T* const, const std::string&);

private:
	template <typename U, typename V> using Map = std::unordered_map<U, V>;

	static	unsigned int						m_count;
	static	Map<unsigned int, T*>				m_objectsByIndex;
	static	Map<std::string, std::vector<T*>>	m_objectsByName;

	const	std::string							m_name{ "" };
	const	unsigned int						m_index{ 0 };
};

template <typename T>
unsigned int Handler<T>::m_count = 0;

template <typename T>
Handler<T>::Map<unsigned int, T*> Handler<T>::m_objectsByIndex;

template <typename T>
Handler<T>::Map<std::string, std::vector<T*>> Handler<T>::m_objectsByName;

template <typename T>
Handler<T>::Handler(T* const object, const std::string& name) : m_name(name), m_index(m_count++) {
	m_objectsByIndex.emplace(m_index, object);
	m_objectsByName[m_name].push_back(object);
}

template <typename T>
Handler<T>::~Handler() {
	T* object = m_objectsByIndex[m_index];
	m_objectsByIndex.erase(m_index);

	auto &vec = m_objectsByName[m_name];
	vec.erase(std::remove(vec.begin(), vec.end(), object), vec.end());
	vec.shrink_to_fit();
}

template <typename T>
const unsigned int Handler<T>::getIndex() const {
	return m_index;
}

template <typename T>
const std::string& Handler<T>::getName() const {
	return m_name;
}

template <typename T>
T* Handler<T>::getWithIndex(const unsigned int index) {
	return m_objectsByIndex[index];
}

template <typename T>
T* Handler<T>::getWithName(const std::string& name) {
	return m_objectsByName[name].front();
}

template <typename T>
T** Handler<T>::getAllWithName(const std::string& name) {
	return m_objectsByName[name].data();
}