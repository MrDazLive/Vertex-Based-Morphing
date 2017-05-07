#include "LocalMorphScene2.h"

#include <Engine\Scene\GameObject\Collider.h>

#include "..\Component\PointMorph.h"
#include "..\Component\MorphRenderable.h"

LocalMorphScene2::LocalMorphScene2(const std::string& name) : Scene(name) {
    AddGameObject(GameObject::getWithName("morph"));
    AddGameObject(GameObject::getWithName("root"));
    AddGameObject(GameObject::getWithName("target"));
}

void LocalMorphScene2::OnOpen() {
    Scene::OnOpen();
}

void LocalMorphScene2::OnFocusEnter() {
    GameObject* ptr = nullptr;

    ptr = GameObject::getWithName("morph");
    ptr->transform->setPosition({ 0.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 1.8f, 1.8f, 1.8f });
    ptr->GetComponent<Collider>()->setMesh("hand");
    ptr->GetComponent<PointMorph>()->setRange(4.0f);
    ptr->GetComponent<PointMorph>()->setWeight(1.0f);
    ptr->GetComponent<MorphRenderable>()->setMaterial("Local_Morph");
    ptr->GetComponent<MorphRenderable>()->setMorphSet("hand");

    ptr = GameObject::getWithName("root");
    ptr->transform->setPosition({ 10.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 1.2f, 1.2f, 1.2f });
    ptr->renderable->setMesh("hand");
    ptr->renderable->setMaterial("Default");

    ptr = GameObject::getWithName("target");
    ptr->transform->setPosition({ -10.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 1.2f, 1.2f, 1.2f });
    ptr->renderable->setMesh("dragon_hand");
    ptr->renderable->setMaterial("Default");

    Scene::OnFocusEnter();
}

void LocalMorphScene2::OnUpdate() {
    Scene::OnUpdate();
}

void LocalMorphScene2::OnFocusLeave() {
    Scene::OnFocusLeave();
}

void LocalMorphScene2::OnClose() {
    Scene::OnClose();
}
