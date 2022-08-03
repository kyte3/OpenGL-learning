#include "VertexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


/* shaders baby */

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
         0.5f, -1.0f, 0.0f, 0.0f, 1.0f
    };

    /* Buffer buffer buffer buffer buffer */
    VertexBuffer vb (vertices, 15 * sizeof(float));

    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);

    // Vertex Colour
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2*sizeof(float)));

    std::string vertexSrc = R"(
        #version 450 core

        layout(location = 0) in vec2 a_Pos;
        layout(location = 1) in vec3 a_Colour;

        out vec3 v_Colour;

        void main()
        {
            v_Colour = a_Colour;
            gl_Position = vec4(a_Pos.xy, 0.0, 1.0);
        }
    )";

    std::string pixelSrc = R"(
        #version 450 core

        in vec3 v_Colour;

        layout(location = 0) out vec4 u_Colour;

        void main()
        {
            u_Colour = vec4(v_Colour.xyz, 1.0);
        }
    )";

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
