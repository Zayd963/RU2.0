#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Debug.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Tests/TestClearColor.h"
#include "Tests/Test.h"
#include "Tests/TestTexture2D.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW could not init" << std::endl;

    Renderer renderer;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

   
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    Test::Test* currentTest = nullptr;
    Test::TestMenu* menu = new Test::TestMenu(currentTest);
    currentTest = menu;

    menu->RegisterTest<Test::TestClearColor>("Clear Color");
    menu->RegisterTest<Test::TestTexture2D>("Texture Test");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.0f, 0.f, 0.f, 1.f));
        /* Render here */
        renderer.Clear();

      

        ImGui_ImplGlfwGL3_NewFrame();
     
        if (currentTest)
        {
            currentTest->Update(0);
            currentTest->Render();
            ImGui::Begin("test");
            if (currentTest != menu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = menu;
            }
            currentTest->IMGUIRender();
            ImGui::End();

        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}