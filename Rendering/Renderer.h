#pragma once

class Renderer final {
public:
	static void Initialise(int*, char*[]);
	static void Quit();
private:
	Renderer() = default;

	int static m_window;
};
