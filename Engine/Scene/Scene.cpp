#include "Scene.h"

#include "GameObject/GameObject.h"

Scene::Scene(const std::string& name) : Handler<Scene>(this, name) { }

void Scene::OnOpen() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->isActive()) {
			ptr->OnStart();
		}
	}
}

void Scene::OnFocusEnter() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->isActive()) {
			ptr->OnAwake();
		}
	}
}

void Scene::OnUpdate() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->isActive()) {
			ptr->OnUpdate();
		}
	}
}

void Scene::OnFocusLeave() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->isActive()) {
			ptr->OnSleep();
		}
	}
}

void Scene::OnClose() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->isActive()) {
			ptr->OnEnd();
		}
	}
}

void Scene::AddGameObject(GameObject* const ptr) {
	m_gameObject.push_back(ptr);
}