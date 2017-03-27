#pragma once

#include <glm\glm.hpp>

#include <Utilities\BaseClass\Handler.h>
#include <Utilities\Container\OctTree.h>

class Mesh;
struct RayHit;

class MeshCollider final : public Handler<MeshCollider> {
public:
                    MeshCollider    (const std::string&);
                    ~MeshCollider   ();

    void            Refresh         ();
    void            Raycast         (const glm::vec3&, const glm::vec3&, RayHit* const);
private:
    Mesh* const                     m_mesh          { nullptr };
    OctTree<unsigned int>           m_octTree       { };
};