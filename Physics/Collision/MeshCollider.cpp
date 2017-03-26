#include "MeshCollider.h"

#include <Utilities\Container\Mesh.h>

#include "RayHit.h"

MeshCollider::MeshCollider(const std::string& name) : Handler<MeshCollider>(this, name), m_mesh(Mesh::getWithName(name)) {
    auto& triangle = [&](unsigned int tri, glm::vec3& val1, glm::vec3& val2, glm::vec3& val3) {
        const unsigned int* ele = m_mesh->getElementArray();
        const glm::vec3* pos = m_mesh->getPositionArray();
        val1 = pos[ele[tri * 3]];
        val2 = pos[ele[tri * 3 + 1]];
        val3 = pos[ele[tri * 3 + 2]];
    };

    auto& mid = [&](unsigned int tri){
        glm::vec3 corner[3];
        triangle(tri, corner[0], corner[1], corner[2]);
        return (((corner[0] + corner[1]) / 2.0f) + corner[2]) / 2.0f;
    };
    auto& min = [&](unsigned int tri) {
        glm::vec3 corner[3];
        triangle(tri, corner[0], corner[1], corner[2]);
        glm::vec3 low;
        low.x = glm::min(glm::min(corner[0].x, corner[1].x), corner[2].x);
        low.y = glm::min(glm::min(corner[0].y, corner[1].y), corner[2].y);
        low.z = glm::min(glm::min(corner[0].z, corner[1].z), corner[2].z);
        return low;
    };
    auto& max = [&](unsigned int tri) {
        glm::vec3 corner[3];
        triangle(tri, corner[0], corner[1], corner[2]);
        glm::vec3 high;
        high.x = glm::max(glm::max(corner[0].x, corner[1].x), corner[2].x);
        high.y = glm::max(glm::max(corner[0].y, corner[1].y), corner[2].y);
        high.z = glm::max(glm::max(corner[0].z, corner[1].z), corner[2].z);
        return high;
    };

    const unsigned int triCount = m_mesh->getTriangleCount();
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < triCount; i++) { indices.push_back(i); }

    m_octTree.setBranchByMedian();

    m_octTree.setValueMethod(Axis::X, [&](unsigned int tri) { return mid(tri).x; });
    m_octTree.setValueMethod(Axis::Y, [&](unsigned int tri) { return mid(tri).y; });
    m_octTree.setValueMethod(Axis::Z, [&](unsigned int tri) { return mid(tri).z; });

    m_octTree.setMinMethod(Axis::X, [&](unsigned int tri) { return min(tri).x; });
    m_octTree.setMinMethod(Axis::Y, [&](unsigned int tri) { return min(tri).y; });
    m_octTree.setMinMethod(Axis::Z, [&](unsigned int tri) { return min(tri).z; });

    m_octTree.setMaxMethod(Axis::X, [&](unsigned int tri) { return max(tri).x; });
    m_octTree.setMaxMethod(Axis::Y, [&](unsigned int tri) { return max(tri).y; });
    m_octTree.setMaxMethod(Axis::Z, [&](unsigned int tri) { return max(tri).z; });

    auto& dist = [&](float min, float max, float div) {int out = 0; if (max < div) out--; if (min > div) out++; return out; };
    m_octTree.setDistributeMethod(Axis::X, [&](unsigned int tri, float div) { return dist(min(tri).x, max(tri).x, div); });
    m_octTree.setDistributeMethod(Axis::Y, [&](unsigned int tri, float div) { return dist(min(tri).y, max(tri).y, div); });
    m_octTree.setDistributeMethod(Axis::Z, [&](unsigned int tri, float div) { return dist(min(tri).z, max(tri).z, div); });

    m_octTree.Populate(indices.data(), triCount);
}

MeshCollider::~MeshCollider() {

}

void MeshCollider::Raycast(const glm::vec3& position, const glm::vec3& direction, RayHit* const hit) {
    const unsigned int range = 200;
    const glm::vec3& dir = glm::normalize(direction);

    for (float i = 0; i <= range; i += 0.1f) {
        m_octTree.Collect(position + (dir * i), hit->triangles);
        if (!hit->triangles.empty()) {
            hit->detected = true;
            break;
        }
    }

    if (hit->detected) hit->meshIndex = m_mesh->getIndex();
}