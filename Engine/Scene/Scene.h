#pragma once

#include <Utilities\BaseClass\Handler.h>
#include <Engine\Scene\GameObject\GameObject.h>

class GameObject;

class Scene abstract : public Handler<Scene> {
public:
                    Scene           (const std::string&);
                    ~Scene          () = default;

    virtual void    OnOpen          ();
    virtual void    OnFocusEnter    ();
    virtual void    OnUpdate        ();
    virtual void    OnFocusLeave    ();
    virtual void    OnClose         ();
protected:
    void            AddGameObject   (GameObject* const);
private:
    std::vector<GameObject*> m_gameObject;
};