#include "Engine.h"
#include "Scene/TestsSceneOne.h"
#include "imgui/imgui_impl_glfw_gl3.h"
GLFWwindow* Engine::window = nullptr;

void Engine::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW could not init" << std::endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    glfwSwapInterval(1);
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

  
}

void Engine::Update()
{
    
}

void Engine::Render()
{

    
    Renderer renderer;
    TestsSceneOne* scene = new TestsSceneOne();
    while (!glfwWindowShouldClose(window))
    {
        
        GLCall(glClearColor(0.0f, 0.f, 0.f, 1.f));
        /* Render here */
        renderer.Clear();

        scene->Update(0.0016);
        scene->Render();

        ImGui_ImplGlfwGL3_NewFrame();


        ImGui::Begin("");
        scene->IMGUIRender();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void Engine::Shutdown()
{
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
