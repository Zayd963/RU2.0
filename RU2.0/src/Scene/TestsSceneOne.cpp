#include "TestsSceneOne.h"
#include <iostream>
#include <array>
#include "core/Input.h"
TestsSceneOne::TestsSceneOne()
{
    texture = std::make_unique<Texture>("res/textures/DefaultTexture.png");
    texture1 = std::make_unique<Texture>("res/textures/Study#1.png");
    texture2 = std::make_unique<Texture>("res/textures/Star.png");
    camera = std::make_unique<Camera>();
    Renderer2D::Init();
}

glm::vec3 pos = { 0, 0, 0 };
float roatation = 0.0f;
void TestsSceneOne::Update(float deltaTime)
{
    roatation += 200 * deltaTime;
   // camera->position.x = -pos.x;
    camera->Update(deltaTime);
    
    

}
float size = 100;
void TestsSceneOne::Render()
{
    texture->Bind(1);
    texture1->Bind(2);
    texture2->Bind(3);
    Renderer2D::Begin(*camera);
    Renderer2D::DrawQuad(pos, 100, { 1.0f, 0.5f, 0.8f, 1.0f }, roatation);
    Renderer2D::DrawQuad({ 100, 100, 0 }, size, 1, roatation);
    Renderer2D::DrawQuad({ 400, 0, 0 }, size, 2, roatation);
    Renderer2D::DrawQuad({ -200, 0, 0 }, size, 3, roatation);
    Renderer2D::End();
}

void TestsSceneOne::IMGUIRender()
{
    ImGui::SliderFloat("X", &camera->position.x, -500, 500);
    ImGui::SliderFloat("Y", &camera->position.y, -500, 500);
    ImGui::SliderFloat("Z", &camera->position.z, -750, 0);
    ImGui::SliderFloat("Camera Speed", &camera->cameraSpeed, 0, 1000);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
