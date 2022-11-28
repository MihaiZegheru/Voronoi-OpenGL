#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <window.h>
#include <apptime.h>
#include <renderer.h>



int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 1000;

void OnWindowResize(GLFWwindow* window, int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GenerateDummyVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}


int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Voronoi");

    Time::GetInstance().Init(glfwGetTime());

    Renderer::Init();


    glfwSetFramebufferSizeCallback(window.GetInstance(), OnWindowResize);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2, 0.2, 0.2, 1);

    glfwSetInputMode(window.GetInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    while (!glfwWindowShouldClose(window.GetInstance())) {
        Time::GetInstance().ComputeDeltaTime(glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
        GenerateDummyVAO();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.GetInstance());
        glfwPollEvents();
    }
    Renderer::Destroy();

    glfwDestroyWindow(window.GetInstance());
    glfwTerminate();

    return 0;
}