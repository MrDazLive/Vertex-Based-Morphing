#include "PointMorph.h"

#include "MorphRenderable.h"

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>
#include <Engine\Scene\GameObject\GameObject.h>

#include <Physics\Physics.h>
#include <Physics\Collision\RayHit.h>

#include <Rendering\Camera\Camera.h>
#include <Rendering\Geometry\MorphSet.h>

PointMorph::PointMorph(GameObject* const ptr) : BaseComponent<PointMorph>(this, ptr) {
    Requires<MorphRenderable>();
}

float const PointMorph::getRange() const {
    return m_morphRange;
}

float const PointMorph::getWeight() const {
    return m_morphWeight;
}

void PointMorph::setRange(const float val) {
    m_morphRange = val;
}

void PointMorph::setWeight(const float val) {
    m_morphWeight = val;
}

void PointMorph::OnAwake() {
    m_morphSet = Requires<MorphRenderable>()->getMorphSet();

    Mesh* const mesh = Mesh::getWithIndex(m_morphSet->getMeshSet()[0]);
    m_positions = mesh->getPositionArray();
    m_elements = mesh->getElementArray();

    m_neighbours.clear();
    m_neighbours.reserve(mesh->getVertexCount());
    m_neighbours.resize(mesh->getVertexCount());

    for (unsigned int index = 0; index < mesh->getElementCount(); index += 3) {
        unsigned int vert[3]{
            m_elements[index],
            m_elements[index + 1],
            m_elements[index + 2]
        };

        m_neighbours[vert[0]].push_back(vert[1]);
        m_neighbours[vert[0]].push_back(vert[2]);

        m_neighbours[vert[1]].push_back(vert[0]);
        m_neighbours[vert[1]].push_back(vert[2]);

        m_neighbours[vert[2]].push_back(vert[0]);
        m_neighbours[vert[2]].push_back(vert[1]);
    }

    for (Neighbour& n : m_neighbours) {
        std::sort(n.begin(), n.end());
        n.erase(unique(n.begin(), n.end()), n.end());
    }
}

void PointMorph::OnUpdate() {
    int multi{ 0 };
    multi += Input::getButton(KeyCode::LEFT_MOUSE, KeyState::HOLD);
    multi -= Input::getButton(KeyCode::RIGHT_MOUSE, KeyState::HOLD);

    if (multi != 0) {
        RayHit hit;
        if (Physics::Raycast(Camera::Position(), Camera::DirectionFromPoint(Input::getCursorPosition()), &hit)) {
            std::vector<float> weights;
            weights.reserve(m_neighbours.size());
            weights.resize(m_neighbours.size());

            Distribute(m_elements[hit.triangle * 3], m_morphRange, weights, hit.point);
            Distribute(m_elements[hit.triangle * 3 + 1], m_morphRange, weights, hit.point);
            Distribute(m_elements[hit.triangle * 3 + 2], m_morphRange, weights, hit.point);

            const float scale = multi * m_morphWeight * Time::getDeltaTime();
            for (unsigned int index = 0; index < weights.size(); index++) {
                const float weight = weights[index];
                if (weight > 0.0f) {
                    m_morphSet->AdjustWeight(index, scale * weight);
                }
            }
        }
    }
}

void PointMorph::Distribute(const unsigned int index, const float range,
    std::vector<float>& weights, const glm::vec3& point) {

    const glm::vec3 pos = m_positions[index];
    const float dis = glm::distance(pos, point);

    if (dis < range) {
        const float eff = (range - dis) / range;
        if (weights[index] < eff) {
            weights[index] = eff;
            for (unsigned int next : m_neighbours[index]) {
                if (weights[next] < eff) {
                    Distribute(next, range - dis, weights, point);
                }
            }
        }
    }
}