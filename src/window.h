#ifndef SRC_WINDOW_WINDOW_H__
#define SRC_WINDOW_WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
	static Window* GetInstance();
	~Window();

	/**
	* @brief Initialise the Window
	*
	* @param windowWidth
	* @param windowHeight
	* @param windowName
	*
	*/
	void Init(int windowWidth, int windowHeight, const char* windowName);

	inline GLFWwindow* GetGlfwInstance() const { return m_GLFWWindow; }
	inline int GetWindowWidth() { return m_windowWidth; }
	inline int GetWindowHeight() { return m_windowHeight; }

	inline void SetFunctionCallbackOnWindowResize(
		void (*functionCallbackOnWindowResize)(GLFWwindow*, int, int)) {
		m_FunctionCallbackOnWindowResize = functionCallbackOnWindowResize;
	}


	/**
	* @brief Window resize Callback
	*
	*/
	static void OnWindowResizeCallback(GLFWwindow* window, int width, int height);

	/**
	* @brief Resize the Window
	* 
	* @param window
	* @param width
	* @param height
	*
	*/
	void ResizeWindow(GLFWwindow* window, int width, int height);

	int Destroy();

private:
	GLFWwindow* m_GLFWWindow;

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowName;

	void (*m_FunctionCallbackOnWindowResize)(GLFWwindow* window, int width, int height);

	int InitGlfw();
	int InitGlad();
	int CreateWindow();

};


#endif  // SRC_WINDOW_WINDOW_H__
