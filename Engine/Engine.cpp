#include "Engine.h"

#include <GL\glut.h>
#include "Input\Input.h"

void Engine::Initialise(int* argc, char* argv[]) {
	glutKeyboardFunc(Input::KeyboardFunction);
	glutKeyboardUpFunc(Input::KeyboardReleaseFunction);
	glutSpecialFunc(Input::KeyboardSpecialFunction);
	glutSpecialUpFunc(Input::KeyboardSpecialReleaseFunction);
}

void Engine::Loop() {
	glutMainLoop();
}

void Engine::Quit() {

}