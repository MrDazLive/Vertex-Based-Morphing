#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Input\Input.h>

int main(int argc, char* argv[]) {
	Renderer::Initialise(&argc, argv);
	Engine::Initialise(&argc, argv);

	Input::BindKey(KeyCode::ESC, KeyState::Down, Renderer::Quit);

	Engine::Loop();

	return 0;
}