#pragma once

#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Triangle.hpp"
#include "Cube.hpp"

class Application
{
public:
	Application() = default;
	~Application();
	bool Init();
	void Loop();
private:
	GLFWwindow* window = NULL;
	int selectedModel = 0;
	const char* modelsNames[2]{ "Triangle", "Cube" };
	Model* models[2]{ new Triangle(), new Cube() };
};
