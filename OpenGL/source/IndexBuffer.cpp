#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer() : m_Count { 0 }, m_RendererID{ 0 } {

}

IndexBuffer::IndexBuffer(const unsigned int* indiciesData, unsigned int count) {
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	m_Count = count;

	glGenBuffers(1, &m_RendererID);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indiciesData, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}
