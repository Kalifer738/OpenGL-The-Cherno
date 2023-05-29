#pragma once

/// <summary>
/// A vertex buffer, holding vertex data and the size of said data.
/// </summary>
class VertexBuffer {
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
}; 