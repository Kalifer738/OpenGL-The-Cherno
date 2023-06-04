#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "Test.h"

#include "glm.hpp"
#include "./gtc/matrix_transform.hpp"

#include "imgui.h"
#include "example_glfw_opengl3/imgui_impl_opengl3.h"
#include "example_glfw_opengl3/imgui_impl_glfw.h"
#include <testClearColorPicker/TestClearColor.h>
#include <testDrawTriangle/TestDrawTriangle.h>
#include <testDrawTextureOnAQuad/TestDrawTextureOnAQuad.h>




#define M_WINDOW_HEIGHT 960
#define M_WINDOW_WIDTH 540

/// <summary>
/// 
/// </summary>
/// <param name="window">The Opengl Window</param>
/// <param name="io">ImGui IO, no idea why its needed</param>
/// <param name="imGui_show_demo_window">a pointer that poitns to a boolean to enable or disable the demo window</param>
/// <param name="f_currentTest">a pointer, that points to the pointer, that points to the actual object</param>
/// <param name="f_testMenu">a pointer, that points to the pointer, that points to the actual object of the entry point of the test menu</param>
void ImGuiRender(GLFWwindow* window, ImGuiIO& io, bool& imGui_show_demo_window, test::Test** f_currentTest, test::Test* f_testMenu) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (imGui_show_demo_window)
		ImGui::ShowDemoWindow(&imGui_show_demo_window);

	/*ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();*/
	if (f_currentTest) {
		(*f_currentTest)->OnUpdate(0.0f);
		(*f_currentTest)->OnRender();
		ImGui::Begin("Test");
		if (*f_currentTest != f_testMenu && ImGui::Button("<-")) {
			delete (*f_currentTest);
			(*f_currentTest) = nullptr;
			(*f_currentTest) = f_testMenu;
		}
		(*f_currentTest)->OnImGuiRender();
		ImGui::End();

	}
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//ImGui::UpdatePlatformWindows();
	


	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	GLCall(glViewport(0, 0, display_w, display_h));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	ImGui::EndFrame();
}

//Window and input
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* Inicialize() {
	// Inicializing OpenGL, giving hits as to what version to use and profile, compatability, etc.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creating a window, checking if it inicialized properly.
	GLFWwindow* window = glfwCreateWindow(M_WINDOW_HEIGHT, M_WINDOW_WIDTH, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		ASSERT(true);
	}
	glfwMakeContextCurrent(window);


	//Checking if GLAD inicialized properly.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		ASSERT(true);
	}

	//Setting the viewport size and setting the callback function whenever the user resizes the window, 
	//	so that the viewport follow with it.
	glViewport(0, 0, M_WINDOW_HEIGHT, M_WINDOW_WIDTH);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Enabled Alpha blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	std::cout << glGetString(GL_VERSION) << std::endl;

	return window;
}

int main(void) {
	GLFWwindow* window = Inicialize();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestDrawTriangle>("Draw Triangle");
	testMenu->RegisterTest<test::TestDrawTextureOnAQuad>("Draw a Textured Quad");

	

	Renderer renderer;

	// Enable VSync
	GLCall(glfwSwapInterval(1));

	// BEGIN imgui
		const char* glsl_version = "#version 150";
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		// Our state
		bool show_demo_window = true;

	// END imgui

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render loop
	while (!glfwWindowShouldClose(window)) {
		GLCall(glfwPollEvents());
		//processInput(window);

		renderer.Clear();

		ImGuiRender(window, io, show_demo_window, &currentTest, testMenu);
		if (currentTest) {
			currentTest->OnRender();
		}
		
		GLCall(glfwSwapBuffers(window));
	}

	//TODO: setup a test folder with test classes, containing little tests about drawing a triangle, a quad, using shader uniforms, 
	//	drawing a texture, drawing multiple textures, and maybe some imgui tests

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window); 
	glfwTerminate();
	return 0;
}
