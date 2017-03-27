#include "MorphSet.h"

#include <algorithm>

MorphSet::MorphSet(const std::string& name) : Handler<MorphSet>(this, name) {

}

const unsigned int MorphSet::getSetSize() const {
    return (unsigned int)m_meshSet.size();
}

const unsigned int* MorphSet::getMeshSet() const {
    return m_meshSet.data();
}

const float* MorphSet::getWeights() const {
    return m_morphWeights.data();
}

void MorphSet::AdjustWeight(unsigned int triangle, const float& step) {
    const unsigned int* const ptr = Mesh::getWithIndex(m_meshSet[0])->getElementArray();

    unsigned int vertex[3];
    vertex[0] = ptr[triangle * 3];
    vertex[1] = ptr[triangle * 3 + 1];
    vertex[2] = ptr[triangle * 3 + 2];

    for (const unsigned int index : vertex) {
        m_morphWeights[index] = glm::max(0.0f, glm::min(1.0f, m_morphWeights[index] + step));
    }
}

const unsigned int MorphSet::MaxSetSize() {
    return 2;
}

void MorphSet::AddMesh(const std::string& name) {
    Mesh* m = Mesh::getWithName(name);
    m_meshSet.push_back(m->getIndex());
    assert(m->getElementCount() == Mesh::getWithIndex(m_meshSet[0])->getElementCount());
}