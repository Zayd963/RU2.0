#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SDL.h>
class Engine
{
public:
	static void Init();
	static void Update();
	static void Render();
	static void Shutdown();
	inline static SDL_Window* GetWindow() { return window; }
private:
	static SDL_Window* window;
	static SDL_GLContext context;

};

