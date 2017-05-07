#include "LocalMorphScene.h"

#include <Engine\Scene\GameObject\Collider.h>

#include "..\Component\PointMorph.h"
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
    GameObject* ptr = nullptr;

    ptr = GameObject::getWithName("morph");
    ptr->transform->setPosition({ 0.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 7.8f, 7.8f, 7.8f });
    ptr->GetComponent<Collider>()->setMesh("torso");
    ptr->GetComponent<PointMorph>()->setRange(1.0f);
    ptr->GetComponent<PointMorph>()->setWeight(0.5f);
    ptr->GetComponent<MorphRenderable>()->setMaterial("Dragon_Morph");
    ptr->GetComponent<MorphRenderable>()->setMorphSet("torso");

    ptr = GameObject::getWithName("root");
    ptr->transform->setPosition({ 10.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 5.4f, 5.4f, 5.4f });
    ptr->renderable->setMesh("torso");
    ptr->renderable->setMaterial("Torso");

    ptr = GameObject::getWithName("target");
    ptr->transform->setPosition({ -10.0f, -5.0f, 10.0f });
    ptr->transform->setScale({ 5.4f, 5.4f, 5.4f });
    ptr->renderable->setMesh("dragon_torso");
    ptr->renderable->setMaterial("Dragon Torso");

    Scene::OnFocusEnter();
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
