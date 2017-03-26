#include "Physics.h"

#include "Collision\RayHit.h"
#include "Collision\MeshCollider.h"

std::unordered_map<unsigned int, std::vector<Physics::Instance>> Physics::m_colliders;

void Physics::Initialise(int*, char*[]) {

}

void Physics::Loop() {
    m_colliders.clear();
}

void Physics::Quit() {

}

void Physics::AddCollider(const unsigned int mesh, const glm::mat4& transform, const unsigned int index) {
    auto& it = m_colliders.find(mesh);
    if (it == m_colliders.end()) {
        m_colliders.emplace(mesh, std::vector<Instance>());
    }
    m_colliders[mesh].push_back({ transform, index });
}

bool Physics::Raycast(const glm::vec3& position, const glm::vec3& direction) {
    RayHit hit;
    return Raycast(position, direction, &hit);
}

bool Physics::Raycast(const glm::vec3& position, const glm::vec3& direction, RayHit* const hit) {
    if (!hit) return false;
    for (auto& it : m_colliders) {
        MeshCollider* const ptr = MeshCollider::getWithIndex(it.first);
        for (const Instance& instance : it.second) {
            glm::mat4 transform_ = glm::inverse(instance.transform);
            glm::vec4 position_ = transform_ * glm::vec4(position, 0.0f);
            glm::vec3 direction_ = (glm::mat3)transform_ * direction;
            ptr->Raycast(position_, direction_, hit);
            if (hit->detected) {
                hit->colliderIndex = instance.index;
                return true;
            }
        }
    }
    return false;
}