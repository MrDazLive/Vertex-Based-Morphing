#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

int main(int argc, char* argv[]) {
	Engine::Initialise(&argc, argv);
	Renderer::Initialise(&argc, argv);

	return 0;
}