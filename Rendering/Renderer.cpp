#include "Renderer.h"

#include "Camera\Camera.h"
#include "ShaderProgram\Shader.h"
#include "ShaderProgram\Program.h"
#include "BufferObjects\ArrayBuffer.h"

#include <Utilities\Container\Mesh.h>

#include <GL\glut.h>
#include <glm\gtc\type_ptr.hpp>

int Renderer::m_window = 0;

ArrayBuffer* Renderer::m_array = nullptr;
std::vector<Program*> Renderer::m_program;

void Renderer::Initialise(int* argc, char* argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1080, 720);
	m_window = glutCreateWindow("Vertex-Based Rendering");

	glewInit();
	glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

	m_array = new ArrayBuffer(GL_STATIC_DRAW);
	m_array->BufferData(Mesh::getWithName("cone")->getPositionArray(), sizeof(glm::vec3) * Mesh::getWithName("cone")->getVertexCount());

	Program* def = new Program("Default");
	m_program.push_back(def);
	Shader vs(GL_VERTEX_SHADER);
	Shader fs(GL_FRAGMENT_SHADER);

	vs.LoadFromFile("Resource/Shader/red.vs");
	fs.LoadFromFile("Resource/Shader/red.fs");

	def->AddShader(&vs, &fs);
	def->Link();
	def->SetActive();
}

void Renderer::Loop() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLint index = glGetUniformLocation(m_program[0]->getProgram(), "view");
	glUniformMatrix4fv(index, 1, GL_TRUE, glm::value_ptr(Camera::ViewMatrix()));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_array->getBuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, Mesh::getWithName("cone")->getElementCount(), GL_UNSIGNED_INT, Mesh::getWithName("cone")->getElementArray());

	glDisableVertexAttribArray(0);
	
	glutSwapBuffers();
}

void Renderer::Quit() {
	glutDestroyWindow(m_window);
	delete m_array;
	delete[] m_program.data();
}