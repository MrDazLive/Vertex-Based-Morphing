#include "Geometry.h"

#include "..\Camera\Camera.h"
#include "..\ShaderProgram\Program.h"
#include "..\UniformBlocks\Material.h"

#include <glm\gtc\type_ptr.hpp>
#include <Utilities\Container\Mesh.h>

struct Geometry::Command {
	GLuint elementCount;
	GLuint instanceCount;
	GLuint elementIndex;
	GLuint vertexIndex;
	GLuint instanceIndex;
};

void Geometry::FillBuffers() {
	std::vector<unsigned int> elements;
	std::vector<Vertex> vertices;

	Mesh** ptrs = Mesh::getAll();
	const unsigned int meshCount = Mesh::getCount();
	for (unsigned int i = 0; i < meshCount; i++) {
		Mesh* ptr = ptrs[i];
		MeshOffsets data;

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
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4);
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4)));
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4) * 2));
	m_vertexArray.AddAttributeDivisor<glm::mat4>(4, (int*)(sizeof(glm::vec4) * 3));

	ArrayBuffer::Reset();
	ElementBuffer::Reset();
	VertexArray::Reset();
}

void Geometry::Draw() {
	m_vertexArray.SetActive();
	m_elementBuffer.SetActive();

	for (auto& program_it : m_commandList) {
		Program* program = Program::getWithIndex(program_it.first);
		program->SetActive();

		GLint index = glGetUniformLocation(program->getProgram(), "view");
		glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(Camera::ViewMatrix()));

		std::vector<glm::mat4> instances;
		std::vector<Command> commands;

		for (auto& mesh_it : program_it.second) {
			const Mesh* mesh = Mesh::getWithIndex(mesh_it.first);
			Command command;

			command.elementIndex = m_meshOffsets[mesh_it.first].elementOffset;
			command.elementCount = mesh->getElementCount();

			command.vertexIndex = m_meshOffsets[mesh_it.first].vertexOffset;

			command.instanceIndex = commands.size();
			command.instanceCount = mesh_it.second.size();

			commands.push_back(command);
			instances.insert(instances.end(), mesh_it.second.data(), mesh_it.second.data() + command.instanceCount);
		}

		m_instanceBuffer.BufferData(instances.data(), instances.size() * sizeof(glm::mat4));
		m_indirectBuffer.BufferData(commands.data(), commands.size() * sizeof(Command));

		//Command c = commands[0];

		//glDrawElementsBaseVertex(GL_TRIANGLES, c.elementCount, GL_UNSIGNED_INT, (GLintptr*)(c.elementIndex * sizeof(unsigned int)), c.vertexIndex);

		//glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, c.elementCount, GL_UNSIGNED_INT, (GLintptr*)(c.elementIndex * sizeof(unsigned int)), c.instanceCount, c.vertexIndex, c.instanceIndex);

		m_indirectBuffer.SetActive();
		glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, commands.size(), sizeof(Command));
	}

	m_commandList.clear();
}

void Geometry::DrawRequest(const unsigned int mesh, const unsigned int material, const glm::mat4& transform) {
	unsigned int shader = Material::getWithIndex(material)->getShader();

	auto& p_it = m_commandList.find(shader);

	if (p_it == m_commandList.end()) {
		m_commandList.emplace(shader, std::map<unsigned int, std::vector<glm::mat4>>());
		p_it = m_commandList.find(shader);
	}

	auto& m_it = p_it->second.find(mesh);

	if (m_it == p_it->second.end()) {
		p_it->second.emplace(mesh, std::vector<glm::mat4>());
	}
	p_it->second[mesh].push_back(transform);
}