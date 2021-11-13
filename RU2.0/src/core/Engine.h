#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Debug.h"
class Engine
{
public:
	static void Init();
	static void Update();
	static void Render();
	static void Shutdown();
private:
	static GLFWwindow* window;
};
