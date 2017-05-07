#include <Engine\Engine.h>
#include <Physics\Physics.h>
#include <Rendering\Renderer.h>

#include <Utilities\Container\Mesh.h>

#include <Rendering\Camera\Camera.h>
#include <Rendering\Texture\Image.h>
#include <Rendering\Texture\Texture.h>
#include <Rendering\Geometry\MorphSet.h>
#include <Rendering\UniformBlocks\Material.h>

#include <Physics\Collision\MeshCollider.h>

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>

#include <Engine\Scene\GameObject\Collider.h>

#include <Physics\Collision\RayHit.h>

#include "Component\PointMorph.h"

#include "Scene\UniformMorphScene.h"
#include "Scene\LocalMorphScene.h"
#include "Scene\LocalMorphScene2.h"

int main(int argc, char* argv[]) {
#pragma region Utility Set-up

    Mesh objects[4]{ "hand", "dragon_hand", "torso", "dragon_torso" };
    for (Mesh& obj : objects) {
        obj.LoadFromFile("Resource/Mesh/" + obj.getName() + ".obj");
    }
    MeshCollider col("hand");
    MeshCollider col2("torso");

#pragma endregion
#pragma region Renderer Set-up

    Renderer::Initialise(&argc, argv);

    Renderer::CreateTexture("missing");
    Renderer::CreateTexture("red");
    Renderer::CreateTexture("green");
    Renderer::CreateTexture("torso_texture");
    Renderer::CreateTexture("dragon_torso_texture");

    Program::forEach([&](Program* const ptr_p) {
        int offset = 0;
        ptr_p->SetActive();
        Texture::forEach([&](Texture* const ptr_t) {
            ptr_p->BindTexture(ptr_t, "textures[" + std::to_string(offset++) + "]");
        });
    });

    Material::getWithName("Default_Morph")->setDiffuse("green");
    Material::getWithName("Default_Morph")->setMorphDiffuse("red");

    Material::getWithName("Local_Morph")->setDiffuse("green");
    Material::getWithName("Local_Morph")->setMorphDiffuse("red");

    {
        Material* ptr = Renderer::CreateMaterial("Dragon_Morph");
        ptr->setShader("Local_Morph");
        ptr->setDiffuse("torso_texture");
        ptr->setMorphDiffuse("dragon_torso_texture");
    }

    Renderer::CreateMaterial("Torso")->setDiffuse("torso_texture");
    Renderer::CreateMaterial("Dragon Torso")->setDiffuse("dragon_torso_texture");

    MorphSet ms_h("hand");
    ms_h.setMorphSet("hand", "dragon_hand");

    MorphSet ms_t("torso");
    ms_t.setMorphSet("torso", "dragon_torso");

    Renderer::ConfirmMorphSets();

#pragma endregion
#pragma region Engine Set-up

    Engine::Initialise(&argc, argv);

    GameObject g("morph");
    g.renderable->setActive(false);
    g.AddComponent<Collider>();
    g.AddComponent<PointMorph>();

    GameObject g2("root");
    g2.renderable->setMaterial("Default");

    GameObject g3("target");
    g3.renderable->setMaterial("Default");

    UniformMorphScene uniform_scene("Uniform Morph");
    LocalMorphScene local_scene("Local Morph");
    LocalMorphScene2 local_scene_2("Local Morph 2");

    Engine::OpenScene("Local Morph");

#pragma endregion
#pragma region Input Bindings

    Input::BindKey(KeyCode::ESC, KeyState::DOWN, []() { Engine::Quit(); Physics::Quit(); Renderer::Quit(); });

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
    Input::BindKey(KeyCode::NUM2, KeyState::DOWN, []() { Engine::SwapScene("Local Morph"); });
    Input::BindKey(KeyCode::NUM3, KeyState::DOWN, []() { Engine::SwapScene("Local Morph 2"); });

#pragma endregion

    Engine::Loop();

    Engine::Quit();
    Physics::Quit();
    Renderer::Quit();

    return 0;
}