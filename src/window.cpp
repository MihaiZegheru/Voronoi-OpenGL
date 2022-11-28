#include <window.h>

#include <debug.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Window::Window(int windowWidth, int windowHeight, const char* windowName)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_windowName = windowName;
    InitGlfw();
    CreateWindow();
    InitGlad();
}

Window::~Window()
{
    Destroy();
}

int Window::CreateWindow()
{
    m_GlfwWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName, nullptr, nullptr);


    if (m_GlfwWindow == nullptr) {
        Debug::LogError("Failed to create Window. Aborting...");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_GlfwWindow);

    return 0;
}

int Window::InitGlfw()
{
    int err = glfwInit();
    if (!err)
    {
        Debug::LogError("Failed to Init GLFW. Aborting...");
        glfwTerminate();
        return err;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

int Window::InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Debug::LogError("Failed to Init Glad. Aborting...");
        //glfwTerminate();
        return -1;
    }
    if (!GLAD_GL_ARB_direct_state_access) {
        Debug::LogError("DSA not supported. Aborting...");
        glfwTerminate();
        return -1;
    }

    return 0;
}

int Window::Destroy()
{
    glfwDestroyWindow(m_GlfwWindow);
    glfwTerminate();

    return 0;
}
