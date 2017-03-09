#include "MorphGeometry.h"

#include "MorphSet.h"
#include "..\Renderer.h"
#include "..\Camera\Camera.h"
#include "..\ShaderProgram\Program.h"
#include "..\UniformBlocks\Material.h"

#include <glm\gtc\type_ptr.hpp>
#include <Utilities\Container\Mesh.h>

void MorphGeometry::FillBuffers() {
    std::vector<unsigned int> elements;
    std::vector<Vertex> vertices;

    MorphSet** sets = MorphSet::getAll();
    const unsigned int setCount = MorphSet::getCount();
    for (unsigned int i = 0; i < setCount; i++) {
        const MorphSet* set = sets[i];
        const unsigned int* ptrs = set->getMeshSet();
        MeshOffsets data;

        const Mesh* ptr = Mesh::getWithIndex(ptrs[0]);
        data.elementCount = ptr->getElementCount();
        data.elementOffset = (unsigned int)elements.size();
        elements.insert(elements.end(), ptr->getElementArray(), ptr->getElementArray() + ptr->getElementCount());

        data.vertexOffset = (unsigned int)vertices.size();
        vertices.insert(vertices.end(), ptr->getVertexArray(), ptr->getVertexArray() + ptr->getVertexCount());

        const unsigned int meshCount = set->getSetSize();
        const unsigned int vertexCount = ptr->getVertexCount();
        for (unsigned int j = 1; j < meshCount; j++) {
            ptr = Mesh::getWithIndex(ptrs[j]);
            const Vertex* vertex = ptr->getVertexArray();
            for (unsigned int k = 0; k < vertexCount; k++) {
                vertices.insert(vertices.begin() + ((j + 1) * k + 1), vertex[k]);
            }
        }

        m_meshOffsets.emplace(set->getIndex(), data);
    }

    m_vertexBuffer.BufferData(vertices.data(), sizeof(Vertex) * vertices.size());
    m_elementBuffer.BufferData(elements.data(), sizeof(unsigned int) * elements.size());

    ArrayBuffer::Reset();
    ElementBuffer::Reset();
}

void MorphGeometry::BuildArray() {
    m_vertexArray.SetActive();
    m_elementBuffer.SetActive();

    m_vertexBuffer.SetActive();
    for (unsigned int i = 0; i < MorphSet::MaxSetSize(); i++) {
        const unsigned int offset = sizeof(Vertex) * i;
        m_vertexArray.AddAttribute<Vertex>(3, MorphSet::MaxSetSize(), (int*)(offset));
        m_vertexArray.AddAttribute<Vertex>(3, MorphSet::MaxSetSize(), (int*)(sizeof(glm::vec3) + offset));
        m_vertexArray.AddAttribute<Vertex>(2, MorphSet::MaxSetSize(), (int*)(sizeof(glm::vec3) * 2 + offset));
    }

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

void MorphGeometry::Draw() {
    m_vertexArray.SetActive();

    for (auto& program_it : m_commandList) {
        Program* program = Program::getWithIndex(program_it.first);
        program->SetActive();

        std::vector<Instance> instances;
        std::vector<Command> commands;

        m_vertexArray.DisableAttributeRange(3, MorphSet::MaxSetSize() * 3);

        for (auto& count_it : program_it.second) {
            for (auto& set_it : count_it.second) {
                Command command;

                command.elementIndex = m_meshOffsets[set_it.first].elementOffset;
                command.elementCount = m_meshOffsets[set_it.first].elementCount;

                command.vertexIndex = m_meshOffsets[set_it.first].vertexOffset;

                command.instanceIndex = (unsigned int)commands.size();
                command.instanceCount = (unsigned int)set_it.second.size();

                commands.push_back(command);
                instances.insert(instances.end(), set_it.second.data(), set_it.second.data() + command.instanceCount);
            }

            m_vertexArray.EnableAttributeRange(3, count_it.first * 3);

            m_instanceBuffer.BufferData(instances.data(), instances.size() * sizeof(Instance));
            m_indirectBuffer.BufferData(commands.data(), commands.size() * sizeof(Command));

            m_indirectBuffer.SetActive();
            GLenum mode = Renderer::getRenderMode() == RenderMode::SHADED ?
                GL_TRIANGLES :
                GL_LINES;
            glMultiDrawElementsIndirect(mode, GL_UNSIGNED_INT, nullptr, (unsigned int)commands.size(), sizeof(Command));
        }
    }

    m_commandList.clear();
}

void MorphGeometry::DrawRequest(const unsigned int morphSet, const unsigned int material, const glm::mat4& transform) {
    unsigned int shader = Material::getWithIndex(material)->getShader();

    auto& p_it = m_commandList.find(shader);

    if (p_it == m_commandList.end()) {
        m_commandList.emplace(shader, std::map<unsigned int, std::map<unsigned int, std::vector<Instance>>>());
        p_it = m_commandList.find(shader);
    }

    const unsigned int count = MorphSet::getWithIndex(morphSet)->getSetSize();
    auto& c_it = p_it->second.find(count);

    if (c_it == p_it->second.end()) {
        p_it->second.emplace(count, std::map<unsigned int, std::vector<Instance>>());
        c_it = p_it->second.find(count);
    }

    auto& s_it = c_it->second.find(morphSet);

    if (s_it == c_it->second.end()) {
        c_it->second.emplace(morphSet, std::vector<Instance>());
    }
    c_it->second[morphSet].push_back({ transform, material });
}