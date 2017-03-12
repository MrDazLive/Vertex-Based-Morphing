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

#include <Utilities\Container\OctTree.h>

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

    GameObject g("morph");
    g.renderable->setActive(false);
	MorphRenderable* r = g.AddComponent<MorphRenderable>();
    r->setMaterial("Default_Morph");

    GameObject g2("root");
    g2.renderable->setMaterial("Default");

    GameObject g3("target");
    g3.renderable->setMaterial("Default");

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

	Input::BindKey(KeyCode::W, KeyState::HOLD, []() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); }); });
    Input::BindKey(KeyCode::S, KeyState::HOLD, []() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(-3.142f, 0.0f, 0.0f) * Time::getDeltaTime()); }); });

    Input::BindKey(KeyCode::A, KeyState::HOLD, []() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(0.0f, 3.142f, 0.0f) * Time::getDeltaTime()); });; });
    Input::BindKey(KeyCode::D, KeyState::HOLD, []() { GameObject::forEach([](GameObject* const ptr) { ptr->transform->Rotate(glm::vec3(0.0f, -3.142f, 0.0f) * Time::getDeltaTime()); }); });

    Input::BindKey(KeyCode::N, KeyState::HOLD, []() { Material::getWithName("Default_Morph")->slideMorph(-Time::getDeltaTime() / 2); });
    Input::BindKey(KeyCode::M, KeyState::HOLD, []() { Material::getWithName("Default_Morph")->slideMorph(Time::getDeltaTime() / 2); });

    Input::BindKey(KeyCode::NUM1, KeyState::DOWN, []() { Engine::SwapScene("Uniform Morph"); });

#pragma endregion

    Engine::Loop();

    Engine::Quit();
    Renderer::Quit();

    return 0;
}