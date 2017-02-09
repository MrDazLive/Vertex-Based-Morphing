#pragma once

class Renderer final {
public:
	static void Initialise(int*, char*[]);
	static void Quit();
private:
	Renderer() = delete;

	int static m_window;
};
