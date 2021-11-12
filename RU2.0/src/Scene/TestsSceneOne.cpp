#include "TestsSceneOne.h"
#include <iostream>

TestsSceneOne::TestsSceneOne()
{
    float positions[] =
    {
         -50.f, -50.0f, 0.0f, 0.0f, 0.0f,
          50.f, -50.0f, 0.0f, 1.0f, 0.0f,
          50.f,  50.0f, 0.0f, 1.0f, 1.0f,
         -50.f,  50.0f, 0.0f, 0.0f, 1.0f,

         100.f, -50.0f, 0.0f, 0.0f, 0.0f,
         300.f, -50.0f, 0.0f, 1.0f, 0.0f,
         300.f,  50.0f, 0.0f, 1.0f, 1.0f,
         100.f,  50.0f, 0.0f, 0.0f, 1.0f



    };

    unsigned int indicies[] =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4

    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
    ibo = std::make_unique<IndexBuffer>(indicies, 12);
    vao = std::make_unique<VertexArray>();
    texture = std::make_unique<Texture>("res/textures/DefaultTexture.png");

    vbo = std::make_unique<VertexBuffer>(positions, 5 * 8 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao->AddBuffer(*vbo, layout);

    translationa = {0, 0, 0};

    proj = glm::perspective(360.f, 4.f / 3.f, 0.f, 100.f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    shader->Bind();


    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

}

void TestsSceneOne::Update(float deltaTime)
{
}

void TestsSceneOne::Render()
{
    Renderer renderer;

    
    shader->Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -250));
    view = glm::translate(glm::mat4(1.0f), translationa);
    glm::mat4 MVP = proj * view * model;
    shader->SetUniformMat4f("u_MVP", MVP);
    renderer.Draw(*vao, *ibo, *shader);
    
}

void TestsSceneOne::IMGUIRender()
{
    ImGui::SliderFloat("X", &translationa.x, -480, 480);
    ImGui::SliderFloat("Y", &translationa.y, -270, 270);
    ImGui::SliderFloat("Z", &translationa.z, -100, 100);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
