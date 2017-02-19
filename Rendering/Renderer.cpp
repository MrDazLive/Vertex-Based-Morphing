#include "Renderer.h"

#include "ShaderProgram\Shader.h"
#include "ShaderProgram\Program.h"
#include "Geometry\Geometry.h"

#include <Utilities\Container\Mesh.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\glut.h>
#include <GLFW\glfw3.h>

int Renderer::m_window = 0;

Geometry* Renderer::m_geometry = nullptr;
std::vector<Program*> Renderer::m_program;

Renderer::~Renderer() {
	Renderer::Quit();
}

void Renderer::Initialise(int* argc, char* argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1080, 720);
	m_window = glutCreateWindow("Vertex-Based Rendering");

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glewInit();
	glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

	m_geometry = new Geometry();
	m_geometry->FillBuffers();
	m_geometry->BuildArray();

	Program* def = new Program("Default");
	m_program.push_back(def);

	Shader r_vs(GL_VERTEX_SHADER);
	Shader r_fs(GL_FRAGMENT_SHADER);

	r_vs.LoadFromFile("Resource/Shader/red.vs");
	r_fs.LoadFromFile("Resource/Shader/red.fs");

	def->AddShader(&r_vs, &r_fs);

	def->AddInAttribute("vertex.position", "vertex.normal", "vertex.uv", "instance.model", "instance.material");
	def->AddOutAttribute("colour");
	def->Link();

	Program* blue = new Program("Blue");
	m_program.push_back(blue);

	Shader b_vs(GL_VERTEX_SHADER);
	Shader b_fs(GL_FRAGMENT_SHADER);

	b_vs.LoadFromFile("Resource/Shader/blue.vs");
	b_fs.LoadFromFile("Resource/Shader/blue.fs");

	blue->AddShader(&b_vs, &b_fs);

	blue->AddInAttribute("vertex.position", "vertex.normal", "vertex.uv", "instance.model", "instance.material");
	blue->AddOutAttribute("colour");
	blue->Link();

	const float aspectRatio = 1080.0f / 720.0f;
	glm::mat4 projection = glm::perspective(1.31f, aspectRatio, 1.0f, 1000.0f);

	for (Program* ptr : m_program) {
		ptr->SetActive();
		GLint index = glGetUniformLocation(ptr->getProgram(), "projection");
		glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(projection));
	}

	Program::Reset();
}

void Renderer::Loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_geometry->Draw();
	
	VertexArray::Reset();
	Program::Reset();

	glutSwapBuffers();
}

void Renderer::Quit() {
	glutDestroyWindow(m_window);

	delete m_geometry;
	m_geometry = nullptr;
	delete[] m_program.data();
	m_program.clear();
}

void Renderer::DrawRequest(const unsigned int mesh, const unsigned int material, const glm::mat4& transform) {
	m_geometry->DrawRequest(mesh, material, transform);
}