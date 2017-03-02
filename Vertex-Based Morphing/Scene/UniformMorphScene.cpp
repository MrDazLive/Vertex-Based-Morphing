#include "UniformMorphScene.h"

UniformMorphScene::UniformMorphScene(const std::string& name) : Scene(name) {
    AddGameObject(GameObject::getWithName("object"));
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
