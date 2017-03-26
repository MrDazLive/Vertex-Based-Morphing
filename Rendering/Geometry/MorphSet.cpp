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

void MorphSet::AdjustWeights(unsigned int* const data, const unsigned int count) {
    std::vector<unsigned int> vertex;
    const unsigned int* const ptr = Mesh::getWithIndex(m_meshSet[0])->getElementArray();
    for (unsigned int i = 0; i < count; i++) {
        vertex.push_back(ptr[data[i]]);
        vertex.push_back(ptr[data[i + 1]]);
        vertex.push_back(ptr[data[i + 2]]);
    }

    std::sort(vertex.begin(), vertex.end());
    vertex.erase(unique(vertex.begin(), vertex.end()), vertex.end());

    for (const unsigned int index : vertex) {
        m_morphWeights[index] = glm::min(1.0f, m_morphWeights[index] + 0.1f);
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