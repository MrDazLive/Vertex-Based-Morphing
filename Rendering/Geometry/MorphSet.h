#pragma once

#include <Utilities\Container\Mesh.h>
#include <Utilities\BaseClass\Handler.h>

#define Variadic template <typename ... V>

class MorphSet final : public Handler<MorphSet> {
public:
                                MorphSet        (const std::string&);
                                ~MorphSet       () = default;

    Variadic void               setMorphSet     (const V&...);

    const unsigned int          getSetSize      () const;
    const unsigned int*         getMeshSet      () const;

    static const unsigned int   MaxSetSize      ();
private:
    void                        AddMesh(const std::string&);
    Variadic void               AddMesh(const std::string&, const V&...);

    std::vector<unsigned int>   m_meshSet;
};

Variadic void MorphSet::setMorphSet(const V&... var) {
    m_meshSet.clear();
    AddMesh(var...);
    assert(m_meshSet.size() <= MaxSetSize());
}

Variadic void MorphSet::AddMesh(const std::string& name, const V&... var) {
    AddMesh(name);
    AddMesh(var...);
}