#pragma once

#include "Component.h"

class Mesh;
class Material;

class Renderable final : public BaseComponent<Renderable> {
public:
						Renderable		(GameObject* const);
						~Renderable		() = default;

	void				setMesh			(const std::string&);
	void				setMaterial		(const std::string&);

	Mesh* const 		getMesh			() const;
	Material* const 	getMaterial		() const;

	void				OnUpdate		() override final;
private:
	unsigned int		m_mesh			{ 0 };
	unsigned int		m_material		{ 0 };
};