#include "Renderer.h"

#include <GL\glew.h>
#include <GL\glut.h>

#include "ShaderProgram\Shader.h"
#include "ShaderProgram\Program.h"
#include "BufferObjects\ArrayBuffer.h"

#include <Utilities\Container\Mesh.h>

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
	m_array->BufferData(Mesh::getWithName("cone")->getPositionArray(), sizeof(Vector3) * Mesh::getWithName("cone")->getVertexCount());

	float vec[9] { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	/*Program* def = new Program("Default");
	m_program.push_back(def);
	Shader vs(GL_VERTEX_SHADER);
	Shader fs(GL_FRAGMENT_SHADER);

	vs.LoadFromFile("Resource/Shader/red.vs");
	fs.LoadFromFile("Resource/Shader/red.fs");

	def->AddShader(&vs, &fs);
	def->Link();
	def->SetActive();*/
}

void Renderer::Loop() {
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_array->getBuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, Mesh::getWithName("cone")->getElementCount());

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void Renderer::Quit() {
	glutDestroyWindow(m_window);
	delete m_array;
	delete[] m_program.data();
}