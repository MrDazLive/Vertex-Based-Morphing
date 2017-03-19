#pragma once

#include <Utilities\BaseClass\Handler.h>
#include <Utilities\Container\OctTree.h>

class Mesh;

class MeshCollider final : public Handler<MeshCollider> {
public:
                    MeshCollider    (const std::string&);
                    ~MeshCollider   ();


private:
    Mesh* const                     m_mesh          { nullptr };
    OctTree<unsigned int>           m_octTree       { };
};