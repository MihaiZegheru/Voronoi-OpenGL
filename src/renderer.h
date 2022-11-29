#ifndef SRC_RENDERER_H__
#define SRC_RENDERER_H__

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Renderer
{
	GLuint Init();
	void Destroy();

	/**
	* @brief Generate empty vao
	*
	*/
	void GenerateDummyVAO();
};

#endif  // SRC_RENDERER_H__