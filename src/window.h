#ifndef SRC_WINDOW_WINDOW_H__
#define SRC_WINDOW_WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
	Window(int windowWidth, int windowHeight, const char* windowName);
	~Window();

	inline GLFWwindow* GetInstance() const { return m_GlfwWindow; }
	inline int GetWindowWidth() { return m_windowWidth; }
	inline int GetWindowHeight() { return m_windowHeight; }

	int Destroy();

private:
	GLFWwindow* m_GlfwWindow;

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowName;

	int InitGlfw();
	int InitGlad();
	int CreateWindow();
};


#endif  // SRC_WINDOW_WINDOW_H__
