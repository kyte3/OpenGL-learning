#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(unsigned int width, unsigned int height, const std::string& title)
{
    glfwInit();
	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_Window)
        glfwTerminate();

    glfwMakeContextCurrent((GLFWwindow*)m_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow*)m_Window);
}

void Window::ShutDown()
{
    glfwTerminate();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose((GLFWwindow*)m_Window);
}
