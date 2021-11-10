#include "Test.h"
#include <imgui/imgui.h>

namespace Test
{
	TestMenu::TestMenu(Test*& currentTestptr)
		:currentTest(currentTestptr)
	{
	}

	void TestMenu::IMGUIRender()
	{
		for (auto& test : tests)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				currentTest = test.second();
			}
		}
	}
}
