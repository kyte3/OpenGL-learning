#include "VertexBuffer.h"
#include <glad/glad.h>


unsigned int GetShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Bool:      return 1;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 4 * 2;
        case ShaderDataType::Int3:      return 4 * 3;
        case ShaderDataType::Int4:      return 4 * 4;
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 4 * 2;
        case ShaderDataType::Float3:    return 4 * 3;
        case ShaderDataType::Float4:    return 4 * 4;
        case ShaderDataType::Mat3:      return 4 * 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4 * 4;
    }
    return 0;
}

VertexBufferElement::VertexBufferElement(ShaderDataType type, const std::string& name, bool normalized)
    : Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
{
}

VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements)
    : m_Elements(elements)
{
    CalculateOffsetAndStride();
}

void VertexBufferLayout::CalculateOffsetAndStride()
{
    unsigned int offset = 0;
    m_Stride = 0;
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }

    m_Stride = offset;
}

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

