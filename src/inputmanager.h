#ifndef SRC_INPUTMANAGER_H__
#define SRC_INPUTMANAGER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include <debug.h>


class InputManager
{
public:
	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	void Listen(GLFWwindow* window)
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

    float GetAxis(std::string axis)
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

    glm::vec2 GetMousePosition()
    {
        return m_mousePosition;
    }

    bool GetKey(std::string key)
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

private:
    InputManager() { 
        m_horizontal = 0; 
        m_vertical = 0; 
        m_jump = false;
        m_leftshift = false;
        m_Q = false;
        m_mousePosition = glm::vec2(0, 0);
    }

	InputManager(InputManager const&) = delete;
	void operator= (InputManager const&) = delete;

    float m_horizontal;
    float m_vertical;

    bool m_jump;
    bool m_leftshift;

    bool m_Q;

    glm::vec2 m_mousePosition;

	static void KeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{

		}
	}
};

#endif  // SRC_INPUTMANAGER_H__