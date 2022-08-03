#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* vertices,unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

private:
	unsigned int m_RendererID;
};