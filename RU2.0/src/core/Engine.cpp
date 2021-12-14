#include "Engine.h"
#include "Scene/TestsSceneOne.h"
#include "imgui/imgui_impl_sdl_gl3.h"
#include "Debug.h"
#include "Input.h"
#include <SDL.h>
SDL_Window* Engine::window = nullptr;
SDL_GLContext Engine::context = NULL;
void getInstalledOpenGLInfo(int* major, int* minor) {
    /// You can to get some info regarding versions and manufacturer
    const GLubyte* version = glGetString(GL_VERSION);
    /// You can also get the version as ints	
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "OpenGL Version: " << version << std::endl;
    std::cout << "Vendor: " << vendor << std::endl;
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "GLSL Version: " << glslVersion << std::endl;

    glGetIntegerv(GL_MAJOR_VERSION, major);
    glGetIntegerv(GL_MINOR_VERSION, minor);
   
    return;
}

void setAttributes(int major_, int minor_) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    SDL_GL_SetSwapInterval(1);
    glewExperimental = GL_TRUE;
    return;
}
void Engine::Init()
{

   if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
       std::cout << "SDL failed to init" << std::endl;
   }

   

    /* Create a windowed mode window and its OpenGL context */
    window = SDL_CreateWindow("RU", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    /* Make the window's context current */
    SDL_GL_CreateContext(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW could not init" << std::endl;

   

    context = SDL_GL_CreateContext(window);
    int major, minor;
    getInstalledOpenGLInfo(&major, &minor);
    setAttributes(major, minor);

    glViewport(0, 0, 1280, 720);
  
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSdlGL3_Init(window);
    ImGui::StyleColorsDark();
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
   
  
}

void Engine::Update()
{
    
}

void Engine::Render()
{

    
    Renderer renderer;
    TestsSceneOne* scene = new TestsSceneOne();
    SDL_Event event;
   
    bool run = true;
    while (run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSdlGL3_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                run = false;
        }
        Input::Listen();
        if (Input::isKeyUp(SDL_SCANCODE_ESCAPE))
            run = false;

        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        renderer.Clear();
        scene->Update(0.016);
        scene->Render();

        ImGui_ImplSdlGL3_NewFrame(window);

        scene->IMGUIRender();
        
      
        ImGui::Render();
        ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        
 
    }
    delete scene;
}

void Engine::Shutdown()
{
    ImGui_ImplSdlGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
