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

Mesh* const Renderable::getMesh() const {
    return Mesh::getWithIndex(m_mesh);
}

Material* const Renderable::getMaterial() const {
    return Material::getWithIndex(m_material);
}

void Renderable::OnUpdate() {
    const glm::mat4 transform = getGameObject()->transform->getTransformMatrix();
    Renderer::DrawRequest(m_mesh, m_material, transform);
}