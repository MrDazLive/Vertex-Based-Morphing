#include "PointMorph.h"

#include "MorphRenderable.h"

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>
#include <Engine\Scene\GameObject\GameObject.h>

#include <Physics\Physics.h>
#include <Physics\Collision\RayHit.h>

#include <Rendering\Camera\Camera.h>
#include <Rendering\Geometry\MorphSet.h>

PointMorph::PointMorph(GameObject* const ptr) : BaseComponent<PointMorph>(this, ptr) {
    Requires<MorphRenderable>();
}

float const PointMorph::getWeight() const {
    return m_morphWeight;
}

void PointMorph::setWeight(const float val) {
    m_morphWeight = val;
}

void PointMorph::OnStart() {
    m_morphSet = Requires<MorphRenderable>()->getMorphSet();
}

void PointMorph::OnUpdate() {
    int multi{ 0 };
    multi += Input::getButton(KeyCode::LEFT_MOUSE, KeyState::HOLD);
    multi -= Input::getButton(KeyCode::RIGHT_MOUSE, KeyState::HOLD);

    if (multi != 0) {
        RayHit hit;
        if (Physics::Raycast(Camera::Position(), Camera::DirectionFromPoint(Input::getCursorPosition()), &hit)) {
            m_morphSet->AdjustWeight(hit.triangle, multi * m_morphWeight * Time::getDeltaTime());
        }
    }
}