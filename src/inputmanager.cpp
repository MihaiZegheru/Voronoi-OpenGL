#include <inputmanager.h>

InputManager& InputManager::GetInstance() {
		static InputManager instance;
		return instance;
}

void InputManager::Listen(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        m_Q = true;
    }
    else {
        m_Q = false;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseY, &mouseX);
    m_mousePosition.x = mouseX;
    m_mousePosition.y = mouseY;
}


bool InputManager::GetKey(std::string key) {
    if (key == "pause")
    {
        return m_Q;
    }
}

InputManager::InputManager() {
    m_Q = false;
    m_mousePosition = glm::vec2(0, 0);
}