#include "Renderer.h"
#include <GL\glut.h>

#include <iostream>

int Renderer::m_window = 0;

void Renderer::Initialise(int* argc, char* argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1080, 720);
	m_window = glutCreateWindow("Vertex-Based Rendering");

	glutMainLoop();
}