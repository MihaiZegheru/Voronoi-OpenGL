#include <window.h>

#include <debug.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static Window* m_instance;

Window* Window::GetInstance() {
    if (m_instance == nullptr) {
        m_instance = new Window();
    }

    return m_instance;

}

void Window::Init(int windowWidth, int windowHeight, const char* windowName) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_windowName = windowName;
    InitGlfw();
    CreateWindow();
    InitGlad();

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.1, 0.1, 0.1, 1);
}

Window::~Window() {
    Destroy();
}


int Window::CreateWindow() {
    m_GLFWWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName, nullptr, nullptr);

    if (m_GLFWWindow == nullptr) {
        Debug::LogError("Failed to create Window. Aborting...");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_GLFWWindow);
    glfwSetFramebufferSizeCallback(m_GLFWWindow, OnWindowResizeCallback);

    return 0;
}

int Window::InitGlfw() {
    int err = glfwInit();
    if (!err) {
        Debug::LogError("Failed to Init GLFW. Aborting...");
        glfwTerminate();
        return err;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

int Window::InitGlad() {
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

void Window::OnWindowResizeCallback(GLFWwindow* window, int width, int height) {
    Window::GetInstance()->ResizeWindow(window, width, height);
}

void Window::ResizeWindow(GLFWwindow* window, int width, int height) {
    int oldWidth = m_windowWidth;
    int oldHeight = m_windowHeight;

    m_windowWidth = width;
    m_windowHeight = height;
    glViewport(0, 0, m_windowWidth, m_windowHeight);

    m_FunctionCallbackOnWindowResize(window, width, height, oldWidth, oldHeight);
}

int Window::Destroy() {
    glfwDestroyWindow(m_GLFWWindow);
    glfwTerminate();

    return 0;
}
