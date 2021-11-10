#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"
namespace Test
{
	TestClearColor::TestClearColor()
		:color {0.2f, 0.3f, 0.8f, 1.0f}
	{

	}

	void TestClearColor::Update(float deltaTime)
	{
	}

	void TestClearColor::Render()
	{
		GLCall(glClearColor(color[0], color[1], color[2], color[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::IMGUIRender()
	{
		ImGui::ColorEdit4("Clear Color", color);
	}

	TestClearColor::~TestClearColor()
	{
		
	}
}