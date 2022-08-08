#pragma once


class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const void* indices, unsigned int size);
	~IndexBuffer();

	void Bind();
	void Unbind();

	unsigned int GetCount() const { return m_Count; };

private:
	unsigned int m_RendererID;
	unsigned int m_Count;

};