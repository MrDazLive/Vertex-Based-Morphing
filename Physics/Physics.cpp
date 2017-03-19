#include "Physics.h"

#include "Collision\RayHit.h"
#include "Collision\MeshCollider.h"

std::unordered_map<unsigned int, std::vector<glm::mat4>> Physics::m_colliders;

void Physics::Initialise(int*, char*[]) {

}

void Physics::Loop() {
    m_colliders.clear();
}

void Physics::Quit() {

}

void Physics::AddCollider(const unsigned int mesh, const glm::mat4& transform) {
    auto& it = m_colliders.find(mesh);
    if (it == m_colliders.end()) {
        m_colliders.emplace(mesh, std::vector<glm::mat4>());
    }
    m_colliders[mesh].push_back(transform);
}

bool Physics::Raycast(const glm::vec3& position, const glm::vec3& direction, RayHit* const hit) {
    for (auto& it : m_colliders) {
        MeshCollider* const ptr = MeshCollider::getWithIndex(it.first);
        for (glm::mat4& transform : it.second) {
            ptr->Raycast(position, direction, hit);
            if (hit->detected) return true;
        }
    }
    return false;
}