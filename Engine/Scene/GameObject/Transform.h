#pragma once

#include "Component.h"
#include <Utilities\Container\Vector3.h>
#include <Utilities\Container\Matrix4.h>

class Transform final : public BaseComponent<Transform> {
public:
						Transform(GameObject* const);
						~Transform();

	const Vector3&		getPosition			() const;
	const Vector3&		getRotation			() const;
	const Vector3&		getScale			() const;
	const Matrix4		getTransformMatrix	() const;

	void				setPosition			(const Vector3&);
	void				setRotation			(const Vector3&);
	void				setScale			(const Vector3&);

	void				Translate			(const Vector3&);
	void				Rotate				(const Vector3&);
private:
	Vector3				m_position			{ 0.0f, 0.0f, 0.0f };
	Vector3				m_rotation			{ 0.0f, 0.0f, 0.0f };
	Vector3				m_scale				{ 1.0f, 1.0f, 1.0f };
};