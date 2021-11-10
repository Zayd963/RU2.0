#pragma once
#include "Test.h"


namespace Test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();

		void Update(float deltaTime) override;
		void Render() override;
		void IMGUIRender() override;

		~TestClearColor();

	private:
		float color[4];
	};


}

