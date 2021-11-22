#include "TestsSceneOne.h"
#include <iostream>
#include <array>
#include "core/Renderer2D.h"

unsigned int offset = 0;
Vertex positions[512];
std::array<Vertex, 4> CreateQuad(const glm::vec3& _position, const float size, const float _texIndex)
{
    

    Vertex v0;
    v0.position = { _position.x, _position.y , 1.0f };
    v0.texCoord = { 0.f, 0.f };
    v0.texIndex = _texIndex;

    Vertex v1;
    v1.position = { _position.x + size, _position.y , 1.0f };
    v1.texCoord = { 1.f, 0.f };
    v1.texIndex = _texIndex;

    Vertex v2;
    v2.position = { _position.x + size, _position.y + size , 1.0f };
    v2.texCoord = { 1.f, 1.f };
    v2.texIndex = _texIndex;

    Vertex v3;
    v3.position = { _position.x, _position.y + size , 1.0f };
    v3.texCoord = { 0.f, 1.f };
    v3.texIndex = _texIndex;

    return { v0, v1, v2, v3 };
}

void DrawQuad(const glm::vec3& position, const float size, const float texIndex)
{
    auto q0 = CreateQuad(position, size, texIndex);
    memcpy(positions + offset, q0.data(), q0.size() * sizeof(Vertex));
    offset += q0.size();
}

void Submit(const glm::vec3& _position, const float size, const float _texIndex)
{

    Vertex v0;
    v0.position = { _position.x, _position.y , 1.0f };
    v0.texCoord = { 0.f, 0.f };
    v0.texIndex = _texIndex;
    memcpy(positions + offset, &v0, sizeof(v0));
    offset++;

    Vertex v1;
    v1.position = { _position.x + size, _position.y , 1.0f };
    v1.texCoord = { 1.f, 0.f };
    v1.texIndex = _texIndex;
    memcpy(positions + offset, &v1, sizeof(v0));
    offset++;

    Vertex v2;
    v2.position = { _position.x + size, _position.y + size , 1.0f };
    v2.texCoord = { 1.f, 1.f };
    v2.texIndex = _texIndex;
    memcpy(positions + offset, &v2, sizeof(v0));
    offset++;

    Vertex v3;
    v3.position = { _position.x, _position.y + size , 1.0f };
    v3.texCoord = { 0.f, 1.f };
    v3.texIndex = _texIndex;
    memcpy(positions + offset, &v3, sizeof(v0));
    offset++;
}

TestsSceneOne::TestsSceneOne()
{
    int texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);

    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Texture Slots: " << texture_units << std::endl;

    texture = std::make_unique<Texture>("res/textures/DefaultTexture.png");
    texture1 = std::make_unique<Texture>("res/textures/Study#1.png");
    texture2 = std::make_unique<Texture>("res/textures/Star.png");
    camera = std::make_unique<Camera>();
    Renderer2D::Init();
}
void TestsSceneOne::Update(float deltaTime)
{
    camera->Update(deltaTime);
}

void TestsSceneOne::Render()
{
    texture->Bind();
    texture1->Bind(1);
    texture2->Bind(2);
    Renderer2D::Begin(*camera);
    Renderer2D::DrawQuad({ 0, 0, 0 }, 100, 0);
    Renderer2D::DrawQuad({ 200, -50, 0 }, 100, 1);
    Renderer2D::DrawQuad({ 300, -50, 0 }, 100, 2);
    Renderer2D::End();
}

void TestsSceneOne::IMGUIRender()
{
    ImGui::SliderFloat("X", &camera->position.x, -2000, 2000);
    ImGui::SliderFloat("Y", &camera->position.y, -2000, 2000);
    ImGui::SliderFloat("Z", &camera->position.z, -2000, 2000);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
