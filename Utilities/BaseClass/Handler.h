#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include "..\Helper\Global.h"

Template
class Handler abstract {
public:
                            ~Handler        ();

    const unsigned int      getIndex        () const;
    const std::string&      getName         () const;

    static unsigned int     getCount        ();

    static T*               getWithName     (const std::string&);
    static T*               getWithIndex    (const unsigned int);

    static T**              getAll          ();
    static T**              getAllWithName  (const std::string&);

    static void             forEach         (std::function<void(T* const)>);
protected:
                            Handler         (T* const, const std::string&);

private:
    template <typename U, typename V> using Map = std::unordered_map<U, V>;

    static unsigned int                         m_count;
    static std::vector<T*>                      m_objectsByIndex;
    static Map<std::string, std::vector<T*>>    m_objectsByName;

    const std::string                           m_name              { "" };
    const unsigned int                          m_index             { 0 };
};

Template
unsigned int Handler<T>::m_count = 0;

Template
std::vector<T*> Handler<T>::m_objectsByIndex;

Template
Handler<T>::Map<std::string, std::vector<T*>> Handler<T>::m_objectsByName;

Template
Handler<T>::Handler(T* const object, const std::string& name) : m_name(name), m_index(m_count++) {
    m_objectsByIndex.push_back(object);
    m_objectsByName[m_name].push_back(object);
}

Template
Handler<T>::~Handler() {
    T* object = m_objectsByIndex[m_index];

    auto& removeFrom = [&](std::vector<T*>& vec) {
        vec.erase(std::remove(vec.begin(), vec.end(), object), vec.end());
        vec.shrink_to_fit();
    };

    removeFrom(m_objectsByIndex);
    removeFrom(m_objectsByName[m_name]);
}

Template
const unsigned int Handler<T>::getIndex() const {
    return m_index;
}

Template
const std::string& Handler<T>::getName() const {
    return m_name;
}

Template
unsigned int Handler<T>::getCount() {
    return (unsigned int)m_objectsByIndex.size();
}

Template
T* Handler<T>::getWithIndex(const unsigned int index) {
    return m_objectsByIndex[index];
}

Template
T* Handler<T>::getWithName(const std::string& name) {
    return m_objectsByName[name].front();
}

Template
T** Handler<T>::getAllWithName(const std::string& name) {
    return m_objectsByName[name].data();
}

Template
T** Handler<T>::getAll() {
    return m_objectsByIndex.data();
}

Template
void Handler<T>::forEach(std::function<void(T* const)> method) {
    for (T* const ptr : m_objectsByIndex) {
        method(ptr);
    }
}