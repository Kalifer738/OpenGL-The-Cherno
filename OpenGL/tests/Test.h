#pragma once

#include "Renderer.h"
#include "imgui.h"
#include <functional>

#include "glm.hpp"
#include "./gtc/matrix_transform.hpp"

namespace test {
	class Test {
	private:

	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPtr);

		virtual void OnImGuiRender() override;
		
		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

		//template<> 
		//void RegisterTest<TestClearColor>(const std::string& name) {
		//	m_Tests.push_back(std::make_pair(name, []() { return new TestClearColor(); }));
		//}

	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}