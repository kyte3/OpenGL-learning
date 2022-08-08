#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Window.h"

#include <glad/glad.h>

#include <iostream>

int main(void)
{
    Window window(1000, 1000, "Smort");

    float vertices[20] = {
        // X Y R G B
         0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f, 1.0f
    };

    /* Buffer buffer buffer buffer buffer */
    VertexBuffer vb (vertices, 20 * sizeof(float));

    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);

    // Vertex Colour
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2*sizeof(float)));

    unsigned int indices[6] = {
        0, 1, 2,
        3, 1, 0
    };

    IndexBuffer ib(indices, 6);

    Shader shader("res/Shaders/basicShader.glsl");
    shader.Bind();

    while (!window.ShouldClose())
    {
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vb.Bind();
        ib.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

        window.OnUpdate();
    }

    window.ShutDown();
    return 0;
}
