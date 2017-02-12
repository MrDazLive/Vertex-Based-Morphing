#pragma once

#include <vector>

class Program;
class ArrayBuffer;

struct Matrix4;

class Renderer final {
public:
	static void Initialise(int*, char*[]);
	static void Loop();
	static void Quit();

	static void Uniform(const Matrix4&);
private:
	Renderer() = delete;

	int static m_window;

	static ArrayBuffer* m_array;
	static std::vector<Program*> m_program;
};
