#pragma once


/// <summary>
/// Indicie buffer, storing data about which vertex is connected to a another, to form a triangle/s.
/// </summary>
class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	// MyTODO: disallow BINDING a empty index buffer.
	IndexBuffer();
	IndexBuffer(const unsigned int* indiciesData, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; };
}; 