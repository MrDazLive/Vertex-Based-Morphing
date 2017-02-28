#pragma once

#include "UniformBlock.h"

#include <glm\glm.hpp>

class Perspective final : public UniformBlock<Perspective> {
	friend class UniformBlock<Perspective>;
public:
						Perspective		(const std::string&);
						~Perspective	() = default;

	const glm::mat4		getProjection	() const;
	const glm::mat4		getView			() const;

	void				setProjection	(const glm::mat4&);
	void				setView			(const glm::mat4&);
protected:
	void				BuildBlock		(float* const) final override;

	glm::mat4			m_projection	{ 0.0f };
	glm::mat4			m_view			{ 0.0f };
};