#include "MorphSet.h"

MorphSet::MorphSet(const std::string& name) : Handler<MorphSet>(this, name) {

}

const unsigned int MorphSet::getSetSize() const {
    return (unsigned int)m_meshSet.size();
}

const unsigned int* MorphSet::getMeshSet() const {
    return m_meshSet.data();
}

const unsigned int MorphSet::MaxSetSize() {
    return 2;
}

void MorphSet::AddMesh(const std::string& name) {
    Mesh* m = Mesh::getWithName(name);
    m_meshSet.push_back(m->getIndex());
    assert(m->getElementCount() == Mesh::getWithIndex(m_meshSet[0])->getElementCount());
}