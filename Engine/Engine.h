#pragma once

#include <stdio.h>

class Engine final {
public:
	static void Initialise(int* argc, char* argv[]) { printf("Engine"); }
private:
	Engine() = default;
};