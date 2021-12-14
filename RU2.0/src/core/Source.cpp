#include "Engine.h"
#include <GLFW/glfw3.h>
int main(int argc, char* args[])
{
    {
        Engine::Init();
        Engine::Update();
        Engine::Render();
        Engine::Shutdown();
    }

    return 0;
}