#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Time\Time.h>
#include <Engine\Input\Input.h>

#include <Utilities\Container\Mesh.h>
#include <Engine\Scene\GameObject\GameObject.h>
#include <Rendering\Camera\Camera.h>

#include <iostream>

int main(int argc, char* argv[]) {
	Mesh m("cone");
	m.LoadFromFile("Resource/Mesh/cone.obj");

	Renderer::Initialise(&argc, argv);
	Engine::Initialise(&argc, argv);

	Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);
	Input::BindKey(KeyCode::A, KeyState::Hold, []() { Camera::Rotate(glm::vec3(1.0f, 0.0f, 0.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::D, KeyState::Hold, []() { Camera::Rotate(glm::vec3(-1.0f, 0.0f, 0.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::W, KeyState::Hold, []() { Camera::Translate(glm::vec3(0.0f, 0.0f, 100.0f) * Time::getDeltaTime()); });
	Input::BindKey(KeyCode::S, KeyState::Hold, []() { Camera::Rotate(glm::vec3(0.0f, 0.0f, -100.0f) * Time::getDeltaTime()); });

	Engine::Loop();

	return 0;
}