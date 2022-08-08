#pragma once

#include <vector>
#include <string>
#include <initializer_list>

enum class ShaderDataType
{
	None = 0,
	Bool,
	Int, Int2, Int3, Int4,
	Float, Float2, Float3, Float4,
	Mat3, Mat4
};

unsigned int GetShaderDataTypeSize(ShaderDataType type);

struct VertexBufferElement
{
	std::string Name;
	unsigned int Size;
	ShaderDataType Type;
	size_t Offset;
	bool Normalized;

	VertexBufferElement() = default;
	VertexBufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

	unsigned int GetComponentCount() const
	{
		switch (Type)
		{
			case ShaderDataType::Bool:      return 1;
			case ShaderDataType::Int:       return 1;
			case ShaderDataType::Int2:      return 2;
			case ShaderDataType::Int3:      return 3;
			case ShaderDataType::Int4:      return 4;
			case ShaderDataType::Float:     return 1;
			case ShaderDataType::Float2:    return 2;
			case ShaderDataType::Float3:    return 3;
			case ShaderDataType::Float4:    return 4;
			case ShaderDataType::Mat3:      return 9;
			case ShaderDataType::Mat4:      return 16;
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;
	VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);

	unsigned int GetStride() const { return m_Stride; }
	const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

	std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
	void CalculateOffsetAndStride();

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

};

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* vertices,unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetLayout(const VertexBufferLayout& layout) { m_Layout = layout; };
	const VertexBufferLayout& GetLayout() const { return m_Layout; }

private:
	unsigned int m_RendererID;
	VertexBufferLayout m_Layout;


};