#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <window.h>
#include <voronoiseed.h>
#include <apptime.h>
#include <renderer.h>
#include <debug.h>


int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 1000;

#define SEEDS_COUNT 40 

std::vector <VoronoiSeed*> seeds;


void OnWindowResize(GLFWwindow* window, int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

float RandomFloat() {
    return (float)rand() / RAND_MAX;
}

void GenerateDummyVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void GenerateSeeds() {
    for (size_t i = 0; i < SEEDS_COUNT; ++i) {
        glm::vec2 position;
        position.x = RandomFloat() * WINDOW_WIDTH;
        position.y = RandomFloat() * WINDOW_HEIGHT;
        VoronoiSeed* seed = new VoronoiSeed();
    }
}

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Voronoi");

    Time::GetInstance().Init(glfwGetTime());

    GLuint shaderProgram = Renderer::Init();

    glfwSetFramebufferSizeCallback(window.GetInstance(), OnWindowResize);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2, 0.2, 0.2, 1);

    GLint screenRes = glGetUniformLocation(shaderProgram, "screenRes");
    GLint seedPos = glGetUniformLocation(shaderProgram, "seedPos");
    GLint seedColor = glGetUniformLocation(shaderProgram, "seedColor");
    glUniform2f(screenRes, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetInputMode(window.GetInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    while (!glfwWindowShouldClose(window.GetInstance())) {
        Time::GetInstance().ComputeDeltaTime(glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GenerateDummyVAO();
           
        srand(0);

        for (size_t i = 0; i < 10; ++i) {
            glUniform2f(seedPos, RandomFloat() * WINDOW_WIDTH, RandomFloat() * WINDOW_HEIGHT);
            glUniform4f(seedColor, RandomFloat(), RandomFloat(), RandomFloat(), 1);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        glfwSwapBuffers(window.GetInstance());
        glfwPollEvents();
    }

    Renderer::Destroy();

    glfwDestroyWindow(window.GetInstance());
    glfwTerminate();

    return 0;
}