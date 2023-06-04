#pragma once

/// <summary>
/// A vertex buffer, holding vertex data and the size of said data.
/// </summary>
class VertexBuffer {
private:
	unsigned int m_RendererID;

public:
	// MyTODO: disallow BINDING a empty vertex buffer.
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
}; 