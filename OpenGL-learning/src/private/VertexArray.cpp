#include "VertexArray.h"
#include <glad/glad.h>

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	delete m_VertexBuffer;
	delete m_IndexBuffer;

	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::SetVertexBuffer(VertexBuffer* buffer)
{
	m_VertexBuffer = buffer;

	glBindVertexArray(m_RendererID);
	m_VertexBuffer->Bind();

	unsigned int attribIndex = 0;

	const auto& layout = m_VertexBuffer->GetLayout();
	for (const auto& element : layout)
	{

		switch (element.Type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribPointer(attribIndex, element.GetComponentCount(), GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
				attribIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribIPointer(attribIndex, element.GetComponentCount(), GL_INT, layout.GetStride(), (const void*)element.Offset);
				attribIndex++;
				break;
			}
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribIPointer(attribIndex, element.GetComponentCount(), GL_BOOL, layout.GetStride(), (const void*)element.Offset);
				attribIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				unsigned int count = element.GetComponentCount();
				for (unsigned int i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(attribIndex);
					glVertexAttribPointer(attribIndex, count, GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(attribIndex, 1);
					attribIndex++;
				}
				break;
			}
		}
	}
}

void VertexArray::SetIndexBuffer(IndexBuffer* buffer)
{
	m_IndexBuffer = buffer;
	glBindVertexArray(m_RendererID);
	m_IndexBuffer->Bind();
}
