#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <iostream>


namespace Utils {

    static void ParseShader(const std::string& filepath, std::string& vertexSrc, std::string& pixelSrc)
    {
        std::ifstream stream(filepath);

        enum class ShaderType
        {
            None = 0,
            Vertex = 1,
            Pixel = 2
        };

        ShaderType shaderType = ShaderType::None;

        std::string line;
        while (getline(stream, line))
        {
            if (line.find("#type") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    shaderType = ShaderType::Vertex;
                }
                else if (line.find("pixel") != std::string::npos)
                {
                    shaderType = ShaderType::Pixel;
                }
            }
            else
            {
                switch (shaderType)
                {
                case ShaderType::Vertex:    vertexSrc.append(line + "\n"); break;
                case ShaderType::Pixel:     pixelSrc.append(line + "\n"); break;
                }
            }
        }
    }

    static unsigned int CompileShader(const std::string& shaderSrc, unsigned int shaderType)
    {
        unsigned int id = glCreateShader(shaderType);
        const char* src = shaderSrc.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* errMsgBuff = (char*)alloca(length * sizeof(char));

            glGetShaderInfoLog(id, length, &length, errMsgBuff);

            std::cout << "Failed to compile shader" << (shaderType == GL_VERTEX_SHADER ? "vertex shader!" : "pixel shader!") << std::endl;
            std::cout << errMsgBuff << std::endl;

            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    static unsigned int CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        unsigned int program = glCreateProgram();

        unsigned int vs = CompileShader(vertexSrc, GL_VERTEX_SHADER);
        unsigned int ps = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, ps);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(ps);

        return program;
    }

}

Shader::Shader(const std::string& filepath)
{
    std::string vertexSrc, pixelSrc;
    Utils::ParseShader(filepath, vertexSrc, pixelSrc);
    m_RendererID = Utils:: CreateShader(vertexSrc, pixelSrc);
}

Shader::Shader(const std::string& vertexSrc, const std::string& pixelSrc)
{
    m_RendererID = Utils::CreateShader(vertexSrc, pixelSrc);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}
