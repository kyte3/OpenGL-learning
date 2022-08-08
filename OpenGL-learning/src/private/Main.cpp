#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"

#include <glad/glad.h>

#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR] (" << error << ")" << std::endl;
    }
}

int main(void)
{
    Window window(1000, 1000, "Smort");

    VertexArray va;
    
    {

        float vertices[20] = {
            // X Y R G B
             0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f, 1.0f
        };

        unsigned int indices[6] = {
            0, 1, 2,
            3, 1, 0
        };

        /* Buffer buffer buffer buffer buffer */
        VertexBuffer* vb = new VertexBuffer(vertices, 20 * sizeof(float));

        vb->SetLayout({
            {ShaderDataType::Float2, "Position"},
            {ShaderDataType::Float3, "Colour"}
        });

        va.SetVertexBuffer(vb);

        IndexBuffer* ib = new IndexBuffer(indices, 6);
        va.SetIndexBuffer(ib);
    }

    Shader shader("res/Shaders/basicShader.glsl");

    //int location = glGetUniformLocation(shader.GetRendererID(), "u_Colour");
    //glUniform4f(location, 1.0f, 0.0f, 1.0f, 1.0f);

    va.Unbind();
    shader.Unbind();

    while (!window.ShouldClose())
    {

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        va.Bind();
        glDrawElements(GL_TRIANGLES, va.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        window.OnUpdate();
    }

    window.ShutDown();
    return 0;
}
