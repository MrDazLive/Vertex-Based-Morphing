#include "LocalMorphScene.h"

#include <Engine\Scene\GameObject\Collider.h>

#include "..\Component\MorphRenderable.h"

LocalMorphScene::LocalMorphScene(const std::string& name) : Scene(name) {
    AddGameObject(GameObject::getWithName("morph"));
    AddGameObject(GameObject::getWithName("root"));
    AddGameObject(GameObject::getWithName("target"));
}

void LocalMorphScene::OnOpen() {
    Scene::OnOpen();
}

void LocalMorphScene::OnFocusEnter() {
    Scene::OnFocusEnter();

    GameObject* ptr = nullptr;

    ptr = GameObject::getWithName("morph");
    ptr->transform->setPosition({ 0.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 1.8f, 1.8f, 1.8f });
    ptr->GetComponent<Collider>()->setMesh("hand");
    ptr->GetComponent<MorphRenderable>()->setMaterial("Local_Morph");
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

void LocalMorphScene::OnUpdate() {
    Scene::OnUpdate();
}

void LocalMorphScene::OnFocusLeave() {
    Scene::OnFocusLeave();
}

void LocalMorphScene::OnClose() {
    Scene::OnClose();
}
