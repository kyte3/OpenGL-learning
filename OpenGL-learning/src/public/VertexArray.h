#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();

	void SetVertexBuffer(VertexBuffer* buffer);
	void SetIndexBuffer(IndexBuffer* buffer);

	const VertexBuffer* GetVertexBuffer() const { return m_VertexBuffer; }
	const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

private:
	unsigned int m_RendererID;
	
	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;

};