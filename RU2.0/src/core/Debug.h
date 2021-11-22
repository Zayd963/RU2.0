#pragma once
#include <iostream>
#include<GL/glew.h>
#include "Engine.h"
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR && glGetError() != GL_CONTEXT_LOST);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "):" << function
            << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}