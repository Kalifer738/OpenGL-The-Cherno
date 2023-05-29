#include "Renderer.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* fileName, int fileLine) {
	while (GLenum error = glGetError()) {
		char errorInHex[5];
		_itoa_s(error, errorInHex, 16);
		std::cout << "[OpenGL Error 0x" << errorInHex << "] in file(" << fileName << ")" << std::endl <<
			"function(" << functionName << ") line " << fileLine << std::endl;
		return false;
	}
	return true;
}


Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	//GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
