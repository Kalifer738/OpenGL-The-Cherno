#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

#include "glm.hpp"
#include "./gtc/matrix_transform.hpp"
#include "program.h"



#define M_WINDOW_HEIGHT 960
#define M_WINDOW_WIDTH 540



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

	std::cout << glGetString(GL_VERSION) << std::endl;

	return window;
}

int main(void) {
	GLFWwindow* window = Inicialize();

	//Static render of verticies
	float trianglePos[16] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
		/*100.0f, 100.0f, 0.0f, 0.0f,
		200.0f, 100.0f, 1.0f, 0.0f,
		200.0f, 200.0f, 1.0f, 1.0f,
		100.0f, 200.0f, 0.0f, 1.0f*/
	};

	//Instead of repeting each vertex's position multiple times, we store how they are connected.
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	//Enabled Alpha blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	VertexArray va;
	VertexBuffer vb(trianglePos, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2); 
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indicies, 6);

	//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	//glm::vec4 vp(100.0f, 100.0f, 0.0f, 0.0f);
	//glm::vec4 result = proj * vp;
	// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

	// glm::mat4 mvp = proj * view;

	Shader shader("resources/shaders/basic.shader");
	shader.Bind();
	//shader.SetUniformMat4f("u_MVP", mvp);
	//shader.SetUniformMat4f("u_MVP", proj);

	Texture texture("resources/textures/pic.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.UnBind();
	vb.Unbind();
	ib.Unbind();
	shader.UnBind();

	Renderer renderer;

	//float r = 0.5f;
	//float adder = 0.03f;

	// Enable VSync
	GLCall(glfwSwapInterval(1));

	// render loop
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window)) {
		//processInput(window);

		//if (r >= 1.0f) {
		//	adder = -adder;
		//}
		//else if (r <= -1.0f) {
		//	adder = -adder;
		//}
		// shader.SetUniform4f("u_Color", r, 0.5f, 0.5f, 1.0f);
		//r += adder;

		renderer.Clear();
		renderer.Draw(va, ib, shader);

		GLCall(glfwSwapBuffers(window));
		GLCall(glfwPollEvents());
	}

	glfwTerminate();
	return 0;
}
