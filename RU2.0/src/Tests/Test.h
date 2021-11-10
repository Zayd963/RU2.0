#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
namespace Test
{
	class Test
	{
	public:
		Test() {};

		virtual ~Test() {};

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void IMGUIRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestptr);
		virtual void IMGUIRender() override;

		template <typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registring Tests" << name << std::endl;
			tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

		~TestMenu() {}
	private:
		Test* &currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
	};
}