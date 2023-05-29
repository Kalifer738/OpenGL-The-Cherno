#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

//OpenGL error handling
void GLClearError();

bool GLLogCall(const char* functionName, const char* fileName, int fileLine);

class Renderer
{
private:

public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};