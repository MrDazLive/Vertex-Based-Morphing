#pragma once

#include <Utilities\Helper\Global.h>
#include <Utilities\Container\Mesh.h>
#include <Utilities\BaseClass\Handler.h>

class MorphSet final : public Handler<MorphSet> {
public:
                                MorphSet        (const std::string&);
                                ~MorphSet       () = default;

    Variadic void               setMorphSet     (const V&...);

    const unsigned int          getSetSize      () const;
    const unsigned int*         getMeshSet      () const;
    const float*                getWeights      () const;

    void                        AdjustWeight    (unsigned int, const float& = 1.0f);

    static const unsigned int   MaxSetSize      ();
private:
    void                        AddMesh(const std::string&);
    Variadic void               AddMesh(const std::string&, const V&...);

    std::vector<unsigned int>   m_meshSet;
    std::vector<float>          m_morphWeights;
};

Variadic void MorphSet::setMorphSet(const V&... var) {
    m_meshSet.clear();
    AddMesh(var...);
    assert(m_meshSet.size() > 1 && m_meshSet.size() <= MaxSetSize());
    m_morphWeights.clear();
    m_morphWeights.resize(Mesh::getWithIndex(m_meshSet[0])->getVertexCount(), 0.0f);
}

Variadic void MorphSet::AddMesh(const std::string& name, const V&... var) {
    AddMesh(name);
    AddMesh(var...);
}