#pragma once

#include "UniformBlock.h"

#include <algorithm>

class Material final : public UniformBlock<Material> {
	friend class UniformBlock<Material>;
public:
							Material		(const std::string&);
							~Material		() = default;

	const unsigned int		getShader		() const;

	void					setShader		(const std::string&);
protected:
	void					BuildBlock		(float*) final override;

	unsigned int			m_shader		{ 0 };
};