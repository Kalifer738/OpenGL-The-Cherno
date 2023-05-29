#pragma once
#include "VertexBuffer.h"

// defining the class in here, as to not create an infintie loop when including it.
// #include "VertexBufferLayout.h"
class VertexBufferLayout;

/// <summary>
/// A Vertex Array that is sent to the GPU, alongside the meta data of each element and the raw data.
/// </summary>
class VertexArray
{
private: 
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};