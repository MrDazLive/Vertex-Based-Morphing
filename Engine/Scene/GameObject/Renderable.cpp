#include "Renderable.h"

#include "GameObject.h"

#include <Rendering\Renderer.h>
#include <Utilities\Container\Mesh.h>
#include <Rendering\UniformBlocks\Material.h>

Renderable::Renderable(GameObject* const ptr) : BaseComponent<Renderable>(this, ptr) {

}

void Renderable::setMesh(const std::string& name) {
	m_mesh = Mesh::getWithName(name)->getIndex();
}

void Renderable::setMaterial(const std::string& name) {
	m_material = Material::getWithName(name)->getIndex();
}

const unsigned int Renderable::getMesh() const {
	return m_mesh;
}

const unsigned int Renderable::getMaterial() const {
	return m_material;
}

void Renderable::OnUpdate() {
	getGameObject()->transform->getTransformMatrix();
}