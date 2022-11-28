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

        glm::vec4 color;
        color.x = RandomFloat();
        color.y = RandomFloat();
        color.z = RandomFloat();
        color.w = 1.f;

        VoronoiSeed* seed = new VoronoiSeed(position, color);
        seeds.push_back(seed);
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

    // Generate the Voronoi seeds
    GenerateSeeds();

    while (!glfwWindowShouldClose(window.GetInstance())) {
        Time::GetInstance().ComputeDeltaTime(glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GenerateDummyVAO();
        
        // Make a determinstic random sys
        srand(0);


        for (size_t i = 0; i < seeds.size(); ++i) {
            glm::vec2 position = seeds[i]->GetPosition();
            glm::vec4 color = seeds[i]->GetColor();
            glUniform2f(seedPos, position.x, position.y);
            glUniform4f(seedColor, color.x, color.y, color.z, color.w);
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