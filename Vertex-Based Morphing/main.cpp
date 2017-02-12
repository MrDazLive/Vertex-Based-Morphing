#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Input\Input.h>

#include <Utilities\Container\Mesh.h>

#include <iostream>

int main(int argc, char* argv[]) {
	Mesh m("cone");
	m.LoadFromFile("Resource/Mesh/box.obj");

	Renderer::Initialise(&argc, argv);
	Engine::Initialise(&argc, argv);

	Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);

	Engine::Loop();

	return 0;
}