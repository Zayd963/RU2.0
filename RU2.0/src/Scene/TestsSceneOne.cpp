#include "TestsSceneOne.h"
#include <iostream>
#include <array>
struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
    int texIndex;
};

std::array<Vertex, 4> CreateQuad(glm::vec2 _position, int _texIndex)
{
    float size = 100.f;

    Vertex v0;
    v0.position = { _position.x, _position.y , 0.0f };
    v0.texCoord = { 0.f, 0.f };
    v0.texIndex = _texIndex;

    Vertex v1;
    v1.position = { _position.x + size, _position.y , 0.0f };
    v1.texCoord = { 1.f, 0.f };
    v1.texIndex = _texIndex;

    Vertex v2;
    v2.position = { _position.x + size, _position.y + size , 0.0f };
    v2.texCoord = { 1.f, 1.f };
    v2.texIndex = _texIndex;

    Vertex v3;
    v3.position = { _position.x, _position.y + size , 0.0f };
    v3.texCoord = { 0.f, 1.f };
    v3.texIndex = _texIndex;

    return { v0, v1, v2, v3 };
}

TestsSceneOne::TestsSceneOne()
{
   /* float positions[] =
    {
         -50.f, -50.0f, 0.0f, 0.0f, 0.0f, 0.0f,
          50.f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f,
          50.f,  50.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         -50.f,  50.0f, 0.0f, 0.0f, 1.0f, 0.0f,

         100.f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         300.f, -50.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         300.f,  50.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         100.f,  50.0f, 0.0f, 0.0f, 1.0f, 1.0f



    };*/

    auto q0 = CreateQuad({ -50, -50 }, 0);
    auto q1 = CreateQuad({ 100, -50 }, 1);

    Vertex positions[8];
    memcpy(positions, q0.data(), q0.size() * sizeof(Vertex));
    memcpy(positions + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

    std::cout << positions[2].texIndex << std::endl;

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
    texture1 = std::make_unique<Texture>("res/textures/Study#1.png");

    vbo = std::make_unique<VertexBuffer>(positions, sizeof(Vertex) * 8);

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<int>(1);
    vao->AddBuffer(*vbo, layout);

    translationa = {0, 0, 0};

    proj = glm::perspective(360.f, 4.f / 3.f, 0.f, 100.f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    shader->Bind();


    texture->Bind(1);
    texture1->Bind();
    int samplers[2] = { 0, 1 };
    shader->SetUniform1iv("u_Texture", samplers, 2);

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
