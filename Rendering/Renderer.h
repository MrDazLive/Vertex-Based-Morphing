#pragma once

#include <vector>

class Program;
class ArrayBuffer;

class Renderer final {
public:
	static void Initialise(int*, char*[]);
	static void Loop();
	static void Quit();
private:
	Renderer() = delete;

	int static m_window;

	static ArrayBuffer* m_array;
	static std::vector<Program*> m_program;
};
