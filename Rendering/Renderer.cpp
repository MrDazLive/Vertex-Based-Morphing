#include "Renderer.h"

#include "Camera\Camera.h"
#include "ShaderProgram\Shader.h"
#include "ShaderProgram\Program.h"
#include "Geometry\Geometry.h"

#include <Utilities\Container\Mesh.h>

#include <GL\glut.h>
#include <glm\gtc\type_ptr.hpp>

int Renderer::m_window = 0;

Geometry* Renderer::m_geometry = nullptr;
std::vector<Program*> Renderer::m_program;

Renderer::~Renderer() {
	Renderer::Quit();
}

void Renderer::Initialise(int* argc, char* argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1080, 720);
	m_window = glutCreateWindow("Vertex-Based Rendering");

	const float aspectRatio = 1080.0f / 720.0f;
	glm::mat4 projection = glm::perspective(1.31f, aspectRatio, 1.0f, 1000.0f);

	glewInit();
	glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

	m_geometry = new Geometry();
	m_geometry->FillBuffers();
	m_geometry->BuildArray();

	Program* def = new Program("Default");
	m_program.push_back(def);

	Shader vs(GL_VERTEX_SHADER);
	Shader fs(GL_FRAGMENT_SHADER);

	vs.LoadFromFile("Resource/Shader/red.vs");
	fs.LoadFromFile("Resource/Shader/red.fs");

	def->AddShader(&vs, &fs);

	def->AddInAttribute("position", "normal", "uv");
	def->AddOutAttribute("colour");
	def->Link();

	def->SetActive();
	GLint index = glGetUniformLocation(m_program[0]->getProgram(), "projection");
	glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(projection));

	index = glGetUniformLocation(m_program[0]->getProgram(), "model");
	glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	Program::Reset();
}

void Renderer::Loop() {
	glClear(GL_COLOR_BUFFER_BIT);

	m_program[0]->SetActive();
	m_geometry->ActivateArray();

	GLint index = glGetUniformLocation(m_program[0]->getProgram(), "view");
	glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(Camera::ViewMatrix()));

	//glDrawElements(GL_TRIANGLES, Mesh::getWithName("cone")->getElementCount(), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, Mesh::getWithName("cone")->getElementCount(), GL_UNSIGNED_INT, Mesh::getWithName("cone")->getElementArray());
	glDrawElementsBaseVertex(GL_TRIANGLES, Mesh::getWithName("cone")->getElementCount(), GL_UNSIGNED_INT, Mesh::getWithName("cone")->getElementArray(), 0);// Mesh::getWithName("cone")->getVertexCount());
	
	VertexArray::Reset();
	Program::Reset();

	glutSwapBuffers();
}

void Renderer::Quit() {
	glutDestroyWindow(m_window);
	delete m_geometry;
	delete[] m_program.data();
}

void Renderer::DrawRequest(const unsigned int mesh, const unsigned int material, const glm::mat4& transform) {

}