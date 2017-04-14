#pragma once

#include <vector>
#include <algorithm>

#include <Utilities\Helper\Global.h>

class GameObject;

class Component abstract {
public:
    virtual const unsigned int  getIndex        () const = 0;

                                ~Component      ();

    GameObject* const           getGameObject   () const;
    const bool                  isActive        () const;
    const void                  setActive       (bool);

    virtual void                OnStart         () {}
    virtual void                OnAwake         () {}
    virtual void                OnUpdate        () {}
    virtual void                OnSleep         () {}
    virtual void                OnEnd           () {}

    virtual void                OnEnable        () {}
    virtual void                OnDisable       () {}
protected:
                                Component       (GameObject* const);
    static unsigned int         getNewIndex     ();

    Template T* const           Requires        ();
private:
    bool                        m_active        { true };
    GameObject* const           m_gameObject    { nullptr };

    static unsigned int         m_count;
};

Template
T* const Component::Requires() {
    T* ptr = m_gameObject->GetComponent<T>();
    return ptr ?
        ptr :
        m_gameObject->AddComponent<T>();
}

Template
class BaseComponent abstract : public Component {
public:
                                ~BaseComponent  ();

    const unsigned int          getIndex        () const override final;

    static T**                  getAll          ();
protected:
                                BaseComponent   (T* const, GameObject* const);
private:
    const T* const              m_self          { nullptr };

    static unsigned int         m_index;
    static std::vector<T*>      m_instance;
};

Template
unsigned int BaseComponent<T>::m_index = Component::getNewIndex();

Template
std::vector<T*> BaseComponent<T>::m_instance;

Template
BaseComponent<T>::BaseComponent(T* const com, GameObject* const obj) : Component(obj), m_self(com) {
    m_instance.push_back(com);
}

Template
BaseComponent<T>::~BaseComponent() {
    m_instance.erase(std::remove(m_instance.begin(), m_instance.end(), m_self), m_instance.end());
    m_instance.shrink_to_fit();
}

Template
const unsigned int BaseComponent<T>::getIndex() const {
    return m_index;
}

Template
T** BaseComponent<T>::getAll() {
    return m_instance.data();
}