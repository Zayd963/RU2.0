#include "Engine.h"
int main(void)
{
    Engine::Init();
    Engine::Update();
    Engine::Render();
    Engine::Shutdown();

    
    return 0;
}