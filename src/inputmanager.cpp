#include <inputmanager.h>

InputManager& InputManager::GetInstance() {
		static InputManager instance;
		return instance;
}

void InputManager::Listen(GLFWwindow* window)
{
    // Vertical Axis
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_vertical = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        if (m_vertical > 0)
        {
            m_vertical = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_vertical = -1;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        if (m_vertical < 0)
        {
            m_vertical = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_vertical = 0;
    }

    // Horizontal Axis
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_horizontal = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        if (m_horizontal > 0)
        {
            m_horizontal = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_horizontal = -1;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        if (m_horizontal < 0)
        {
            m_horizontal = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_horizontal = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_jump = true;
    }
    else
    {
        m_jump = false;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_leftshift = true;
    }
    else
    {
        m_leftshift = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_Q = true;
    }
    else
    {
        m_Q = false;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseY, &mouseX);
    m_mousePosition.x = mouseX;
    m_mousePosition.y = mouseY;
}

float InputManager::GetAxis(std::string axis)
{
    if (axis == "horizontal")
    {
        return m_horizontal;
    }
    if (axis == "vertical")
    {
        return m_vertical;
    }
}

bool InputManager::GetKey(std::string key)
{
    if (key == "jump")
    {
        return m_jump;
    }
    if (key == "leftshift")
    {
        return m_leftshift;
    }
    if (key == "pause")
    {
        return m_Q;
    }
}

InputManager::InputManager() {
    m_horizontal = 0;
    m_vertical = 0;
    m_jump = false;
    m_leftshift = false;
    m_Q = false;
    m_mousePosition = glm::vec2(0, 0);
}