#pragma once

#include <Engine\Scene\GameObject\Component.h>

class MorphSet;

class PointMorph final : public BaseComponent<PointMorph> {
public:
                    PointMorph      (GameObject* const);
                    ~PointMorph     () = default;

    float const     getWeight       () const;

    void            setWeight       (const float);

    void            OnStart         () override final;
    void            OnUpdate        () override final;
private:
    MorphSet*       m_morphSet      { nullptr };
    float           m_morphWeight   { 1.0f };
};