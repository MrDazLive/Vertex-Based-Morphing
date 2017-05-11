#pragma once

#include "Component.h"

class MeshCollider;

class Collider final : public BaseComponent<Collider> {
public:
                            Collider    (GameObject* const);
                            ~Collider   () = default;

    void                    setMesh     (const std::string&);

    MeshCollider* const     getMesh     () const;

    void                    OnUpdate    () override final;
private:
    unsigned int            m_mesh      { 0 };
};