#include "VertexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>


/* shaders baby */

static void ParseShader(const std::string& filepath, std::string& vertexSrc, std::string&pixelSrc)
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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Test Window", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* hungry harold */
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* vertices time */
    float vertices[15] = {
        // X Y R G B
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };

    /* Buffer buffer buffer buffer buffer */
    VertexBuffer vb (vertices, 15 * sizeof(float));

    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);

    // Vertex Colour
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2*sizeof(float)));

    std::string vertexSrc, pixelSrc;
    ParseShader("res/Shaders/basicShader.glsl", vertexSrc, pixelSrc);
    unsigned int shader = CreateShader(vertexSrc, pixelSrc);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
