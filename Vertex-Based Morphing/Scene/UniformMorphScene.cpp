#include "UniformMorphScene.h"

#include <Engine\Scene\GameObject\Collider.h>
#include <Engine\Scene\GameObject\MorphRenderable.h>

UniformMorphScene::UniformMorphScene(const std::string& name) : Scene(name) {
    AddGameObject(GameObject::getWithName("morph"));
    AddGameObject(GameObject::getWithName("root"));
    AddGameObject(GameObject::getWithName("target"));
}

void UniformMorphScene::OnOpen() {
    Scene::OnOpen();
}

void UniformMorphScene::OnFocusEnter() {
    Scene::OnFocusEnter();

	GameObject* ptr = nullptr;
		
	ptr = GameObject::getWithName("morph");
	ptr->transform->setPosition({ 0.0f, -5.0f, 10.0f });
	ptr->transform->setScale({ 1.8f, 1.8f, 1.8f });
    ptr->GetComponent<Collider>()->setMesh("hand");
	ptr->GetComponent<MorphRenderable>()->setMorphSet("hand");

	ptr = GameObject::getWithName("root");
	ptr->transform->setPosition({ 10.0f, -5.0f, 10.0f });
	ptr->transform->setScale({ 1.2f, 1.2f, 1.2f });
	ptr->renderable->setMesh("hand");

	ptr = GameObject::getWithName("target");
	ptr->transform->setPosition({ -10.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 1.2f, 1.2f, 1.2f });
	ptr->renderable->setMesh("dragon_hand");
}

void UniformMorphScene::OnUpdate() {
    Scene::OnUpdate();
}

void UniformMorphScene::OnFocusLeave() {
    Scene::OnFocusLeave();
}

void UniformMorphScene::OnClose() {
    Scene::OnClose();
}
