#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Utilities\Container\Mesh.h>

#include <Rendering\Camera\Camera.h>
#include <Rendering\UniformBlocks\Material.h>

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>

#include "Scene\UniformMorphScene.h"

#include <Rendering\Geometry\MorphSet.h>
#include <Engine\Scene\GameObject\MorphRenderable.h>

int main(int argc, char* argv[]) {
#pragma region Utility Set-up

    Mesh objects[3] { "hand", "dragon_hand", "torso" };
    for (Mesh& obj : objects) {
        obj.LoadFromFile("Resource/Mesh/" + obj.getName() + ".obj");
    }

#pragma endregion
#pragma region Renderer Set-up

    Renderer::Initialise(&argc, argv);

    MorphSet ms("hand");
    ms.setMorphSet("hand", "dragon_hand");

    Renderer::ConfirmMorphSets();

#pragma endregion
#pragma region Engine Set-up

    Engine::Initialise(&argc, argv);

    GameObject g("object");
    g.transform->setPosition({ 0.0f, -5.0f, 10.0f });
    g.transform->setScale({ 1.8f, 1.8f, 1.8f });
    g.renderable->setActive(false);
    MorphRenderable* mr = g.AddComponent<MorphRenderable>();
    mr->setMorphSet("hand");
    mr->setMaterial("Default_Morph");


    GameObject g2("object2");
    g2.renderable->setMesh("hand");
    g2.renderable->setMaterial("Default");
    g2.transform->setPosition({ 10.0f, -5.0f, 10.0f });
    g2.transform->setScale({ 1.8f, 1.8f, 1.8f });

    GameObject g3("object3");
    g3.renderable->setMesh("dragon_hand");
    g3.renderable->setMaterial("Default");
    g3.transform->setPosition({ -10.0f, -5.0f, 10.0f });
    g3.transform->setScale({ 1.8f, 1.8f, 1.8f });

    UniformMorphScene uniform_scene("Uniform Morph");

    Engine::OpenScene("Uniform Morph");

#pragma endregion
#pragma region Input Bindings

    Input::BindKey(KeyCode::ESC, KeyState::DOWN, []() { Engine::Quit(); Renderer::Quit(); });

    Input::BindKey(KeyCode::F1, KeyState::DOWN, []() { Renderer::setRenderMode(RenderMode::SHADED); });
    Input::BindKey(KeyCode::F2, KeyState::DOWN, []() { Renderer::setRenderMode(RenderMode::WIREFRAME); });

    Input::BindKey(KeyCode::F5, KeyState::DOWN, []() { Program::forEach([](Program* const ptr) { ptr->setVertexSubroutine("linear"); }); });
    Input::BindKey(KeyCode::F6, KeyState::DOWN, []() { Program::forEach([](Program* const ptr) { ptr->setVertexSubroutine("cosine"); }); });
    Input::BindKey(KeyCode::F7, KeyState::DOWN, []() { Program::forEach([](Program* const ptr) { ptr->setVertexSubroutine("quadratic"); }); });
    Input::BindKey(KeyCode::F8, KeyState::DOWN, []() { Program::forEach([](Program* const ptr) { ptr->setVertexSubroutine("cubic"); }); });

    Input::BindKey(KeyCode::UP, KeyState::HOLD, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, 4.0f) * Time::getDeltaTime()); });
    Input::BindKey(KeyCode::DOWN, KeyState::HOLD, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, -4.0f) * Time::getDeltaTime()); });

	Input::BindKey(KeyCode::W, KeyState::HOLD, [&]() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); }); });
    Input::BindKey(KeyCode::S, KeyState::HOLD, [&]() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(-3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); }); });

    Input::BindKey(KeyCode::A, KeyState::HOLD, [&]() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(0.0f, 3.142f, 0.0f) * Time::getDeltaTime()); });; });
    Input::BindKey(KeyCode::D, KeyState::HOLD, [&]() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(0.0f, -3.142f, 0.0f) * Time::getDeltaTime()); }); });

    Material* material = Material::getWithName("Default_Morph");
    Input::BindKey(KeyCode::N, KeyState::HOLD, [&]() { material->slideMorph(-Time::getDeltaTime() / 2); });
    Input::BindKey(KeyCode::M, KeyState::HOLD, [&]() { material->slideMorph(Time::getDeltaTime() / 2); });

    Input::BindKey(KeyCode::NUM1, KeyState::DOWN, []() { Engine::SwapScene("Uniform Morph"); });

#pragma endregion

    Engine::Loop();

    Engine::Quit();
    Renderer::Quit();

    return 0;
}