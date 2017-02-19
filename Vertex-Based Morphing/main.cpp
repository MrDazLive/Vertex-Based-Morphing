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
	mat.setColour({ 1.0f, 0.5f, 0.5f });

	Material mat2("Material");
	mat2.setShader("Default");
	mat2.setColour({ 0.5f, 1.0f, 0.0f });

	Material::BufferBlock();
	Program** ptrs = Program::getAll();
	const unsigned int count = Program::getCount();
	for (unsigned int i = 0; i < count; i++) {
		Material::BindBlock("Material", ptrs[i]);
	}

	GameObject g("cone");
	g.renderable->setMesh("cone");
	g.renderable->setMaterial("Default");

	GameObject g2("cone2");
	g2.renderable->setMesh("cone");
	g2.renderable->setMaterial("Material");
	g2.transform->setScale({ 1, -1, 1 });

	Scene s("Scene");
	s.AddGameObject(&g);
	s.AddGameObject(&g2);
	Engine::OpenScene("Scene");

	Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);

	Input::BindKey(KeyCode::W, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, 4.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::S, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, -4.0f) * Time::getDeltaTime()); });

	Input::BindKey(KeyCode::A, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, 3.142f, 0.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::D, KeyState::Hold, [&]() { g.transform->Rotate(glm::vec3(0.0f, -3.142f, 0.0f) * Time::getDeltaTime()); });

	Input::BindKey(KeyCode::Q, KeyState::Up, [&]() { mat.setShader("Default"); });
	Input::BindKey(KeyCode::Q, KeyState::Down, [&]() { mat.setShader("Blue"); });

	Input::BindKey(KeyCode::E, KeyState::Up, [&]() { g.renderable->setMaterial("Default"); });
	Input::BindKey(KeyCode::E, KeyState::Down, [&]() { g.renderable->setMaterial("Material"); });

	Engine::Loop();

	Engine::Quit();
	Renderer::Quit();

	return 0;
}