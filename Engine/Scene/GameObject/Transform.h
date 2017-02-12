#pragma once

#include "Component.h"
#include <Utilities\Container\Vector3.h>

class Transform final : public BaseComponent<Transform> {
public:
	Transform(GameObject* const);
	~Transform();


private:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
};