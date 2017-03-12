#include "MorphRenderable.h"

#include "GameObject.h"

#include <Rendering\Renderer.h>
#include <Rendering\Geometry\MorphSet.h>
#include <Rendering\UniformBlocks\Material.h>

MorphRenderable::MorphRenderable(GameObject* const ptr) : BaseComponent<MorphRenderable>(this, ptr) {

}

void MorphRenderable::setMorphSet(const std::string& name) {
    m_morphSet = MorphSet::getWithName(name)->getIndex();
}

void MorphRenderable::setMaterial(const std::string& name) {
    m_material = Material::getWithName(name)->getIndex();
}

MorphSet* const MorphRenderable::getMorphSet() const {
    return MorphSet::getWithIndex(m_morphSet);
}

Material* const MorphRenderable::getMaterial() const {
    return Material::getWithIndex(m_material);
}

void MorphRenderable::OnUpdate() {
    const glm::mat4 transform = getGameObject()->transform->getTransformMatrix();
    Renderer::MorphDrawRequest(m_morphSet, m_material, transform);
}