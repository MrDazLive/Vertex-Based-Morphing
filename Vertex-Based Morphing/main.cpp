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
	Mesh m("cone");
	m.LoadFromFile("Resource/Mesh/cone.obj");

	Mesh m2("box");
	m2.LoadFromFile("Resource/Mesh/box.obj");

	Renderer::Initialise(&argc, argv);
	Engine::Initialise(&argc, argv);

	Material mat("Default");
	mat.setShader("Default");

	GameObject g("cone");
	g.renderable->setMesh("cone");
	g.renderable->setMaterial("Default");

	Scene s("Scene");
	s.AddGameObject(&g);
	Engine::OpenScene("Scene");

	Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);

	Input::BindKey(KeyCode::W, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, 100.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::S, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, -100.0f) * Time::getDeltaTime()); });

	Input::BindKey(KeyCode::A, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, 100.0f, 0.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::D, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, -100.0f, 0.0f) * Time::getDeltaTime()); });

	Input::BindKey(KeyCode::Q, KeyState::Up, [&]() { mat.setShader("Default"); });
	Input::BindKey(KeyCode::Q, KeyState::Down, [&]() { mat.setShader("Blue"); });

	Engine::Loop();

	Engine::Quit();
	Renderer::Quit();

	return 0;
}