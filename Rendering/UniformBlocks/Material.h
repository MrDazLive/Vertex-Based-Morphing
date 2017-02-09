#pragma once

#include "UniformBlock.h"

#include <algorithm>

class Material final : public UniformBlock<Material> {
	friend class UniformBlock<Material>;
public:
	Material(const std::string&);
protected:
	void BuildBlock(float*) final override;
};