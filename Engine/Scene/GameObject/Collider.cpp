#include "Collider.h"

#include "GameObject.h"

#include <Physics\Physics.h>
#include <Physics\Collision\MeshCollider.h>

Collider::Collider(GameObject* const ptr) : BaseComponent<Collider>(this, ptr) {

}

void Collider::setMesh(const std::string& name) {
    m_mesh = MeshCollider::getWithName(name)->getIndex();
}

MeshCollider* const Collider::getMesh() const {
    return MeshCollider::getWithIndex(m_mesh);
}

void Collider::OnUpdate() {
    const glm::mat4 transform = getGameObject()->transform->getTransformMatrix();
    Physics::AddCollider(m_mesh, transform);
}