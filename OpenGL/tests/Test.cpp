#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPtr) : m_currentTest(currentTestPtr) {

	}

	void TestMenu::OnImGuiRender() {
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_currentTest = test.second();
			}
		}
	}
}


