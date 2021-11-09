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

    float positions[] =
    {
         -50.f, -50.0f, 0.0f, 0.0f,
          50.f, -50.0f, 1.0f, 0.0f,
          50.f,  50.0f, 1.0f, 1.0f,
         -50.f,  50.0f, 0.0f, 1.0f

    };

    unsigned int indicies[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6);

    glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
   

    Shader shader("res/shaders/Basic.Shader");
    shader.Bind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    Texture texture("res/textures/DefaultTexture.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
   
    va.UnBind();
    shader.UnBind();
    vb.UnBind();
    ib.UnBind();

    bool one = true;
    glm::vec3 translationa(200, 200, 0);
    glm::vec3 translationb(400, 400, 0);
   
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

       

        va.Bind();
        shader.Bind();
        vb.Bind();
        ib.Bind();
     


        ImGui::SliderFloat2("float", &translationa.x, 0.0f, 960.0f);           
        ImGui::SliderFloat2("float1", &translationb.x, 0.0f, 960.0f);           

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationa);
            glm::mat4 MVP = proj * view * model;
            shader.SetUniformMat4f("u_MVP", MVP);
            renderer.Draw(va, ib, shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationb);
            glm::mat4 MVP = proj * view * model;
            shader.SetUniformMat4f("u_MVP", MVP);
            renderer.Draw(va, ib, shader);
        }
        
      
     

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