#include "Scene.h"

#include "GameObject.h"

Scene::Scene(const std::string& name) : Handler<Scene>(this, name) { }

void Scene::OnUpdate() {
	for (GameObject* const ptr : m_gameObject) {
		if (ptr->active) {
			ptr->OnUpdate();
		}
	}
}

void Scene::AddGameObject(GameObject* const ptr) {
	m_gameObject.push_back(ptr);
}