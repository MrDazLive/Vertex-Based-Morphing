#pragma once

#include "Vertex.h"
#include "..\BaseClass\Handler.h"

class Mesh final : public Handler<Mesh> {
public:
                        Mesh                (const std::string&);
                        ~Mesh                ();

    const unsigned int    getElementCount        () const;
    const unsigned int    getVertexCount        () const;

    const unsigned int*    getElementArray        () const;
    const Vertex*        getVertexArray        () const;
    const glm::vec3*        getPositionArray    () const;
    const glm::vec3*        getNormalArray        () const;
    const glm::vec2*        getUVArray            () const;

    void                LoadFromFile        (const std::string&);
private:
    std::vector<unsigned int> m_elementArray;
    std::vector<Vertex> m_vertexArray;
    std::vector<glm::vec3> m_positionsArray;
    std::vector<glm::vec3> m_normalArray;
    std::vector<glm::vec2> m_uvArray;
};