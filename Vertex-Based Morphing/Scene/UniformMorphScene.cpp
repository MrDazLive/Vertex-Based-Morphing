#include "UniformMorphScene.h"

UniformMorphScene::UniformMorphScene(const std::string& name) : Scene(name) {
    AddGameObject(GameObject::getWithName("object"));
    AddGameObject(GameObject::getWithName("object3"));
    AddGameObject(GameObject::getWithName("object2"));
}

void UniformMorphScene::OnOpen() {
    Scene::OnOpen();
}

void UniformMorphScene::OnFocusEnter() {
    Scene::OnFocusEnter();
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
