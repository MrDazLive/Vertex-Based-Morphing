#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>

#include <Utilities\Container\Mesh.h>
#include <Engine\Scene\Scene.h>
#include <Engine\Scene\GameObject\GameObject.h>
#include <Rendering\Camera\Camera.h>
#include <Rendering\UniformBlocks\Material.h>

#include <iostream>

int main(int argc, char* argv[]) {
    Mesh objects[3] { "hand", "dragon_hand", "torso" };
    for (Mesh& obj : objects) {
        obj.LoadFromFile("Resource/Mesh/" + obj.getName() + ".obj");
    }

    Renderer::Initialise(&argc, argv);
    Engine::Initialise(&argc, argv);

    Material mat("Default");
    mat.setShader("Default");

    Material::BufferBlock();
    Program** ptrs = Program::getAll();
    const unsigned int count = Program::getCount();
    for (unsigned int i = 0; i < count; i++) {
        Material::BindBlock("Block_Material", ptrs[i]);
    }

    GameObject g("object");
    g.renderable->setMesh("torso");
    g.renderable->setMaterial("Default");
    //g.transform->setPosition({ 0.0f, -5.0f, 10.0f });
    g.transform->setScale({ 1.8f, 1.8f, 1.8f });

    Scene s("Scene");
    s.AddGameObject(&g);
    Engine::OpenScene("Scene");

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

    Engine::Loop();

    Engine::Quit();
    Renderer::Quit();

    return 0;
}