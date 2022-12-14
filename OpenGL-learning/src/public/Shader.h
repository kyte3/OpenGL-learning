#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& filepath);
	Shader(const std::string& vertexSrc, const std::string& pixelSrc);
	~Shader();

	void Bind();
	void Unbind();

	unsigned int GetRendererID() const { return m_RendererID; }

private:
	unsigned int m_RendererID;

};