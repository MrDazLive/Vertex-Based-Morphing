#pragma once

class Engine final {
public:
	static void Initialise(int*, char*[]);
	static void Loop();
	static void Quit();
private:
	Engine() = default;
};