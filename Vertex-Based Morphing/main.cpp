#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>

#include <Utilities\Container\Mesh.h>
#include <Rendering\Camera\Camera.h>
#include <Rendering\UniformBlocks\Material.h>

#include "Scene\UniformMorphScene.h"

#include <iostream>

int main(int argc, char* argv[]) {
#pragma region Utility Set-up

    Mesh objects[3] { "hand", "dragon_hand", "torso" };
    for (Mesh& obj : objects) {
        obj.LoadFromFile("Resource/Mesh/" + obj.getName() + ".obj");
    }

#pragma endregion
#pragma region Renderer Set-up

    Renderer::Initialise(&argc, argv);

#pragma endregion
#pragma region Engine Set-up

    Engine::Initialise(&argc, argv);

    GameObject g("object");
    g.renderable->setMesh("hand");
    g.renderable->setMaterial("Default");
    g.transform->setPosition({ 0.0f, -5.0f, 10.0f });
    g.transform->setScale({ 1.8f, 1.8f, 1.8f });

    UniformMorphScene uniform_scene("Uniform Morph");

    Engine::OpenScene("Uniform Morph");

#pragma endregion
#pragma region Input Bindings

    Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);

    Input::BindKey(KeyCode::UP, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, 4.0f) * Time::getDeltaTime()); });
    Input::BindKey(KeyCode::DOWN, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, -4.0f) * Time::getDeltaTime()); });

    Input::BindKey(KeyCode::W, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); });
    Input::BindKey(KeyCode::S, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(-3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); });

    Input::BindKey(KeyCode::A, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, 3.142f, 0.0f) * Time::getDeltaTime()); });
    Input::BindKey(KeyCode::D, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, -3.142f, 0.0f) * Time::getDeltaTime()); });

    Input::BindKey(KeyCode::Q, KeyState::Up, [&]() { g.renderable->getMaterial()->setShader("Default"); });
    Input::BindKey(KeyCode::Q, KeyState::Down, [&]() { g.renderable->getMaterial()->setShader("Blue"); });

    Input::BindKey(KeyCode::E, KeyState::Up, [&]() { g.renderable->setMesh("hand"); });
    Input::BindKey(KeyCode::E, KeyState::Down, [&]() { g.renderable->setMesh("dragon_hand"); });

    Input::BindKey(KeyCode::NUM1, KeyState::Down, []() { Engine::SwapScene("Uniform Morph"); });

#pragma endregion

    Engine::Loop();

    Engine::Quit();
    Renderer::Quit();

    return 0;
}