#include <Engine\Engine.h>
#include <Rendering\Renderer.h>

#include <Engine\Scene\Scene.h>
#include <Engine\Scene\GameObject.h>

#include <iostream>

int main(int argc, char* argv[]) {
	Engine::Initialise(&argc, argv);
	//Renderer::Initialise(&argc, argv);

	Scene t1[5]{ { "Scene" },{ "Scene" },{ "Top" },{ "Scene" },{ "Scene" } };
	GameObject t2[5]{ { "Object" },{ "Bottom" },{ "Bottom" },{ "Object" },{ "Object" } };

	Scene **a1 = Scene::getAllWithName("Scene");
	GameObject **a2 = GameObject::getAllWithName("Object");

	std::cout << a1[0]->getIndex() << std::endl;
	std::cout << a1[1]->getIndex() << std::endl;
	std::cout << a1[2]->getIndex() << std::endl;
	std::cout << a1[3]->getIndex() << std::endl;

	std::cout << std::endl;

	std::cout << a2[0]->getIndex() << std::endl;
	std::cout << a2[1]->getIndex() << std::endl;
	std::cout << a2[2]->getIndex() << std::endl;

	return 0;
}