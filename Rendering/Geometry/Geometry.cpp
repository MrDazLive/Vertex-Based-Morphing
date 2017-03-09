#include "Geometry.h"

#include "..\Renderer.h"
#include "..\ShaderProgram\Program.h"
#include "..\UniformBlocks\Material.h"

#include <glm\gtc\type_ptr.hpp>
#include <Utilities\Container\Mesh.h>

void Geometry::FillBuffers() {
    std::vector<unsigned int> elements;
    std::vector<Vertex> vertices;

    Mesh** ptrs = Mesh::getAll();
    const unsigned int meshCount = Mesh::getCount();
    for (unsigned int i = 0; i < meshCount; i++) {
        Mesh* ptr = ptrs[i];
        MeshOffsets data;

        data.elementCount = ptr->getElementCount();
        data.elementOffset = (unsigned int)elements.size();
        elements.insert(elements.end(), ptr->getElementArray(), ptr->getElementArray() + ptr->getElementCount());

        data.vertexOffset = (unsigned int)vertices.size();
        vertices.insert(vertices.end(), ptr->getVertexArray(), ptr->getVertexArray() + ptr->getVertexCount());

        m_meshOffsets.emplace(ptr->getIndex(), data);
    }

    m_vertexBuffer.BufferData(vertices.data(), sizeof(Vertex) * vertices.size());
    m_elementBuffer.BufferData(elements.data(), sizeof(unsigned int) * elements.size());

    ArrayBuffer::Reset();
    ElementBuffer::Reset();
}

void Geometry::BuildArray() {
    m_vertexArray.SetActive();
    m_elementBuffer.SetActive();
    m_vertexBuffer.SetActive();
    m_vertexArray.AddAttribute<Vertex>(3);
    m_vertexArray.AddAttribute<Vertex>(3, (int*)(sizeof(glm::vec3)));
    m_vertexArray.AddAttribute<Vertex>(2, (int*)(sizeof(glm::vec3) * 2));
    m_instanceBuffer.SetActive();
    m_vertexArray.AddAttributeDivisor<Instance>(4);
    m_vertexArray.AddAttributeDivisor<Instance>(4, (int*)(sizeof(glm::vec4)));
    m_vertexArray.AddAttributeDivisor<Instance>(4, (int*)(sizeof(glm::vec4) * 2));
    m_vertexArray.AddAttributeDivisor<Instance>(4, (int*)(sizeof(glm::vec4) * 3));
    m_vertexArray.AddAttributeDivisor<Instance>(1, (int*)(sizeof(glm::vec4) * 4));

    VertexArray::Reset();
    ArrayBuffer::Reset();
    ElementBuffer::Reset();
}

void Geometry::Draw() {
    m_vertexArray.SetActive();

    for (auto& program_it : m_commandList) {
        Program* program = Program::getWithIndex(program_it.first);
        program->SetActive();

        std::vector<Instance> instances;
        std::vector<Command> commands;

        for (auto& mesh_it : program_it.second) {
            Command command;

            command.elementIndex = m_meshOffsets[mesh_it.first].elementOffset;
            command.elementCount = m_meshOffsets[mesh_it.first].elementCount;

            command.vertexIndex = m_meshOffsets[mesh_it.first].vertexOffset;

            command.instanceIndex = (unsigned int)commands.size();
            command.instanceCount = (unsigned int)mesh_it.second.size();

            commands.push_back(command);
            instances.insert(instances.end(), mesh_it.second.data(), mesh_it.second.data() + command.instanceCount);
        }

        m_instanceBuffer.BufferData(instances.data(), instances.size() * sizeof(Instance));
        m_indirectBuffer.BufferData(commands.data(), commands.size() * sizeof(Command));

        m_indirectBuffer.SetActive();
        GLenum mode = Renderer::getRenderMode() == RenderMode::SHADED ?
            GL_TRIANGLES :
            GL_LINES;
        glMultiDrawElementsIndirect(mode, GL_UNSIGNED_INT, nullptr, (unsigned int)commands.size(), sizeof(Command));
    }

    m_commandList.clear();
}

void Geometry::DrawRequest(const unsigned int mesh, const unsigned int material, const glm::mat4& transform) {
    unsigned int shader = Material::getWithIndex(material)->getShader();

    auto& p_it = m_commandList.find(shader);

    if (p_it == m_commandList.end()) {
        m_commandList.emplace(shader, std::map<unsigned int, std::vector<Instance>>());
        p_it = m_commandList.find(shader);
    }

    auto& m_it = p_it->second.find(mesh);

    if (m_it == p_it->second.end()) {
        p_it->second.emplace(mesh, std::vector<Instance>());
    }
    p_it->second[mesh].push_back({ transform, material });
}