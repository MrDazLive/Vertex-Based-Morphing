#include "Engine.h"

#include <GL\glut.h>
#include "Input\Input.h"
#include "Scene\Scene.h"

std::vector<Scene*>	Engine::m_activeScene;

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
	for (Scene* ptr : m_activeScene) {
		ptr->OnFocusLeave();
		ptr->OnClose();
	}
}

void Engine::OpenScene(const std::string& name) {
	SuspendScene();

	Scene* ptr = Scene::getWithName(name);
	m_activeScene.push_back(ptr);

	ptr->OnOpen();
	ptr->OnFocusEnter();
}

void Engine::SwapScene(const std::string& name, const unsigned int level = 0) {
	unsigned int closeCount = m_activeScene.size() > level ? 
		m_activeScene.size() - level :
		0;

	for (unsigned int i = 0; i < closeCount; i++) {
		Scene* ptr = getCurrentScene();
		m_activeScene.pop_back();

		ptr->OnFocusLeave();
		ptr->OnClose();
	}
	OpenScene(name);
}

void Engine::ReloadScene() {
	Scene* ptr = getCurrentScene();

	ptr->OnFocusLeave();
	ptr->OnClose();

	ptr->OnOpen();
	ptr->OnFocusEnter();
}

void Engine::CloseScene() {
	Scene* ptr = getCurrentScene();
	m_activeScene.pop_back();

	ptr->OnFocusLeave();
	ptr->OnClose();

	ResumeScene();
}

void Engine::ResumeScene() {
	Scene* ptr = getCurrentScene();
	if (ptr != nullptr) {
		ptr->OnFocusEnter();
	}
}

void Engine::SuspendScene() {
	Scene* ptr = getCurrentScene();
	if (ptr != nullptr) {
		ptr->OnFocusLeave();
	}
}

Scene* Engine::getCurrentScene() {
	return !m_activeScene.empty() ?
		m_activeScene.back() :
		nullptr;
}