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
    static InputManager& GetInstance();

    void Listen(GLFWwindow* window);

    glm::vec2 GetMousePosition() { return m_mousePosition; }

	/**
    * @brief Get Key pressed
    *
    * @param key
    * @return bool
    */
    bool GetKey(std::string key);

private:
    InputManager();
	InputManager(InputManager const&) = delete;
	void operator= (InputManager const&) = delete;

    bool m_Q;

    glm::vec2 m_mousePosition;

};

#endif  // SRC_INPUTMANAGER_H__