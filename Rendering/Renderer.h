#pragma once

class Renderer final {
public:
	static void Initialise(int*, char*[]);
private:
	Renderer() = default;

	int static m_window;
};
