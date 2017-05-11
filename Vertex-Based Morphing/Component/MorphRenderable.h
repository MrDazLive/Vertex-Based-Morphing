#pragma once

#include <Engine\Scene\GameObject\Component.h>

class MorphSet;
class Material;

class MorphRenderable final : public BaseComponent<MorphRenderable> {
public:
                        MorphRenderable     (GameObject* const);
                        ~MorphRenderable    () = default;

    void                setMorphSet         (const std::string&);
    void                setMaterial         (const std::string&);

    MorphSet* const     getMorphSet         () const;
    Material* const     getMaterial         () const;

    void                OnUpdate            () override final;
private:
    unsigned int        m_morphSet          { 0 };
    unsigned int        m_material          { 0 };
};