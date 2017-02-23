#pragma once

#include "Component.h"

#include <glm\glm.hpp>

class Transform final : public BaseComponent<Transform> {
public:
						Transform(GameObject* const);
						~Transform();

	const glm::vec3&	getPosition			() const;
	const glm::vec3&	getRotation			() const;
	const glm::vec3&	getScale			() const;
	const glm::mat4		getTransformMatrix	() const;

	void				setPosition			(const glm::vec3&);
	void				setRotation			(const glm::vec3&);
	void				setScale			(const glm::vec3&);

	void				Translate			(const glm::vec3&);
	void				Rotate				(const glm::vec3&);
private:
	glm::vec3				m_position			{ 0.0f, 0.0f, 0.0f };
	glm::vec3				m_rotation			{ 0.0f, 0.0f, 0.0f };
	glm::vec3				m_scale				{ 1.0f, 1.0f, 1.0f };
};