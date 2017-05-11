#pragma once

#include "..\VertexObjects\VertexArray.h"
#include "..\BufferObjects\ArrayBuffer.h"
#include "..\BufferObjects\ElementBuffer.h"

#include <map>
#include <glm\glm.hpp>
#include <unordered_map>

class Geometry {
public:
                    Geometry            () = default;
                    ~Geometry           () = default;

    virtual void    FillBuffers         ();
    virtual void    BuildArray          ();

    virtual void    Draw                ();
    virtual void    DrawRequest         (const unsigned int, const unsigned int, const glm::mat4&);
protected:
    struct Command {
        unsigned int elementCount;
        unsigned int instanceCount;
        unsigned int elementIndex;
        unsigned int vertexIndex;
        unsigned int instanceIndex;
    };
    struct Instance {
        glm::mat4 model;
        unsigned int material;
    };
    struct MeshOffsets {
        unsigned int elementCount;
        unsigned int elementOffset;
        unsigned int vertexOffset;
    };

    ArrayBuffer     m_vertexBuffer      { GL_STATIC_DRAW };
    ArrayBuffer     m_instanceBuffer    { GL_DYNAMIC_DRAW };
    BufferObject    m_indirectBuffer    { GL_DRAW_INDIRECT_BUFFER, GL_DYNAMIC_DRAW };
    ElementBuffer   m_elementBuffer     {};
    VertexArray     m_vertexArray       {};

    std::unordered_map<unsigned int, MeshOffsets>                                       m_meshOffsets;
private:

    std::unordered_map<unsigned int, std::map<unsigned int, std::vector<Instance>>>     m_commandList;
};